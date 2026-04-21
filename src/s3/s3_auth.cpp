#include "s3_auth.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "openssl/evp.h"
#include "openssl/hmac.h"
#include "s3_utils.hpp"
#include "spdlog/fmt/ranges.h"
#include "spdlog/spdlog.h"

namespace
{
    std::string bytesToHexLower(const unsigned char* data, size_t len)
    {
        static constexpr char kHex[] = "0123456789abcdef";
        std::string out{};
        out.reserve(len * 2U);
        for (size_t i = 0; i < len; ++i)
        {
            const unsigned char b = data[i];
            out.push_back(kHex[b >> 4U]);
            out.push_back(kHex[b & 0xFU]);
        }
        return out;
    }

    std::string sha256HexDigest(const char* data, int64_t dataLen)
    {
        unsigned int digestLen = 0;
        unsigned char digest[EVP_MAX_MD_SIZE] = {0};
        std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_new(), &EVP_MD_CTX_free);
        (void)EVP_DigestInit_ex(ctx.get(), EVP_sha256(), nullptr);
        (void)EVP_DigestUpdate(ctx.get(), data, static_cast<size_t>(dataLen));
        (void)EVP_DigestFinal_ex(ctx.get(), digest, &digestLen);
        return bytesToHexLower(digest, static_cast<size_t>(digestLen));
    }

    std::string hmacSha256(const std::string& key, const std::string& msg, bool hex)
    {
        unsigned int outLen = 0;
        unsigned char out[EVP_MAX_MD_SIZE] = {0};
        (void)HMAC(EVP_sha256(), key.data(), static_cast<int>(key.size()), reinterpret_cast<const unsigned char*>(msg.data()),
                   static_cast<size_t>(msg.size()), out, &outLen);
        if (false == hex)
        {
            return std::string(reinterpret_cast<const char*>(out), static_cast<size_t>(outLen));
        }

        return bytesToHexLower(out, static_cast<size_t>(outLen));
    }

    std::string ensureUnicode(const std::string& s)
    {
        return s;
    }

    std::string headerValue(const std::string& value)
    {
        /**
         * From the sigv4 docs:
         * Lowercase(HeaderName) + ':' + Trimall(HeaderValue)
         * The Trimall function removes excess white space before and after
         * values, and converts sequential spaces to a single space.
         */
        // fn: _header_value
        std::istringstream ss(value);
        std::string word;
        std::vector<std::string> words;
        while (ss >> word)
        {
            words.push_back(word);
        }
        return fmt::to_string(fmt::join(words, " "));
    }
} // namespace

namespace s3
{
    namespace auth
    {

        std::string percentEncode(const std::string& input, const std::string& safe)
        {
            std::array<bool, 256> safeChars;
            std::fill(safeChars.begin(), safeChars.end(), false);
            for (unsigned char c : safe)
            {
                safeChars[c] = true;
            }

            std::string out;
            out.reserve(input.size() * 3);
            for (const unsigned char c : input)
            {
                if (std::isalnum(static_cast<unsigned char>(c)))
                {
                    out += c;
                }
                else if (safeChars[c])
                {
                    out += c;
                }
                else
                {
                    out += fmt::format("%{:02X}", static_cast<uint8_t>(c));
                }
            }

            return out;
        }

        std::string percentDecode(const char* safe)
        {
            std::string unescaped;

            for (; *safe; safe++)
            {
                switch (*safe)
                {
                case '%': {
                    int hex = 0;
                    auto ch = *++safe;
                    if (ch >= '0' && ch <= '9')
                    {
                        hex = (ch - '0') * 16;
                    }
                    else if (ch >= 'A' && ch <= 'F')
                    {
                        hex = (ch - 'A' + 10) * 16;
                    }
                    else if (ch >= 'a' && ch <= 'f')
                    {
                        hex = (ch - 'a' + 10) * 16;
                    }
                    else
                    {
                        unescaped.push_back('%');
                        if (ch == 0)
                        {
                            return unescaped;
                        }
                        unescaped.push_back(ch);
                        break;
                    }

                    ch = *++safe;
                    if (ch >= '0' && ch <= '9')
                    {
                        hex += (ch - '0');
                    }
                    else if (ch >= 'A' && ch <= 'F')
                    {
                        hex += (ch - 'A' + 10);
                    }
                    else if (ch >= 'a' && ch <= 'f')
                    {
                        hex += (ch - 'a' + 10);
                    }
                    else
                    {
                        unescaped.push_back('%');
                        unescaped.push_back(*(safe - 1));
                        if (ch == 0)
                        {
                            return unescaped;
                        }
                        unescaped.push_back(ch);
                        break;
                    }

                    unescaped.push_back(char(hex));
                    break;
                }
                default:
                    unescaped.push_back(*safe);
                    break;
                }
            }

            return unescaped;
        }
        std::string canonicalHeaders(const std::vector<std::pair<std::string, std::string>>& headersToSign)
        {
            // 去重
            std::unordered_set<std::string> uniqueHeaderNames;
            for (const auto& kv : headersToSign)
            {
                uniqueHeaderNames.insert(kv.first);
            }

            // 排序
            std::vector<std::string> sortedHeaderNames;
            sortedHeaderNames.reserve(uniqueHeaderNames.size());
            for (const std::string& name : uniqueHeaderNames)
            {
                sortedHeaderNames.push_back(name);
            }
            std::sort(sortedHeaderNames.begin(), sortedHeaderNames.end(), std::less<std::string>());

            std::vector<std::string> headers;
            for (const std::string& key : sortedHeaderNames)
            {
                std::string lowerKey = s3::utils::StringUtils::ToLower(key.c_str());
                std::vector<std::string> matchedValues;
                for (const auto& kv : headersToSign)
                {
                    std::string lowerKvKey = s3::utils::StringUtils::ToLower(kv.first.c_str());
                    if (lowerKey == lowerKvKey)
                    {
                        matchedValues.push_back(headerValue(kv.second));
                    }
                }
                std::string value = fmt::to_string(fmt::join(matchedValues, ","));
                headers.push_back(fmt::format("{}:{}", key, ensureUnicode(value)));
            }
            return fmt::to_string(fmt::join(headers, "\n"));
        }

        /**
         * 计算scope
         * @param accessKey
         * @param dateStamp 格式: YYYYMMDD, eg: 20260418
         * @param regionName 区域, eg: us-east-1
         * @param serviceName 服务名, eg: s3
         */
        std::string scope(const std::string& accessKey, const std::string& dateStamp, const std::string& regionName, const std::string& serviceName)
        {
            // fn: scope
            std::vector<std::string> vec{
                accessKey, dateStamp, regionName, serviceName, "aws4_request",
            };
            return fmt::to_string(fmt::join(vec, "/"));
        }

        /**
         * 计算credentialScope
         * @param accessKey
         * @param dateStamp 格式: YYYYMMDD, eg: 20260418
         * @param regionName 区域, eg: us-east-1
         * @param serviceName 服务名, eg: s3
         */
        std::string credentialScope(const std::string& dateStamp, const std::string& regionName, const std::string& serviceName)
        {
            // fn: credential_scope
            std::vector<std::string> vec{
                dateStamp,
                regionName,
                serviceName,
                "aws4_request",
            };
            return fmt::to_string(fmt::join(vec, "/"));
        }

        /**
         * @param secretKey
         * @param dateStamp
         * @param regionName
         * @param serviceName
         * @param stringToSign
         */
        std::string signature(const std::string& secretKey, const std::string& dateStamp, const std::string& regionName,
                              const std::string& serviceName, const std::string& stringToSign)
        {
            const std::string kDate = hmacSha256(fmt::format("AWS4{}", secretKey), dateStamp, false);
            const std::string kRegion = hmacSha256(kDate, regionName, false);
            const std::string kService = hmacSha256(kRegion, serviceName, false);
            const std::string kSigning = hmacSha256(kService, "aws4_request", false);
            return hmacSha256(kSigning, stringToSign, true);
        }

        /**
         * 计算stringToSign
         * @param timestamp 时间戳, eg: 20260418T142320Z
         * @param credentialScope
         * @param canonicalRequest
         */
        std::string stringToSign(const std::string& timestamp, const std::string& credentialScope, const std::string& canonicalRequest)
        {
            // fn: string_to_sign
            const std::string canonicalRequestSha256HexDigest =
                sha256HexDigest(canonicalRequest.data(), static_cast<int64_t>(canonicalRequest.size()));
            std::vector<std::string> vec{
                "AWS4-HMAC-SHA256",
                timestamp,
                credentialScope,
                canonicalRequestSha256HexDigest,
            };
            return fmt::to_string(fmt::join(vec, "\n"));
        }

        /**
         * 计算canonicalRequest
         * @param upperHttpMethod 大写的http方法, eg: GET
         * @param normalizedUrlPath
         * @param canonicalQueryString
         * @param canonicalHeaders
         * @param signedHeaders
         * @param bodyChecksum
         */
        std::string canonicalRequest(const std::string& upperHttpMethod, const std::string& normalizedUrlPath,
                                     const std::string& canonicalQueryString, const std::string& canonicalHeaders, const std::string& signedHeaders,
                                     const std::string& bodyChecksum)
        {
            std::vector<std::string> cr{
                upperHttpMethod, normalizedUrlPath, canonicalQueryString, fmt::format("{}\n", canonicalHeaders), signedHeaders, bodyChecksum,
            };
            return fmt::to_string(fmt::join(cr, "\n"));
        }

        std::string canonicalQueryStringByVecPair(std::vector<std::pair<std::string, std::string>>& encodedPairs)
        {
            std::vector<std::pair<std::string, std::string>>& sortedEncodedPairs = encodedPairs;
            std::sort(sortedEncodedPairs.begin(), sortedEncodedPairs.end(), std::less<std::pair<std::string, std::string>>());

            std::vector<std::string> formattedKeyValue;
            formattedKeyValue.reserve(sortedEncodedPairs.size());
            for (const std::pair<std::string, std::string>& kv : sortedEncodedPairs)
            {
                formattedKeyValue.push_back(fmt::format("{}={}", kv.first, kv.second));
            }
            return fmt::to_string(fmt::join(formattedKeyValue, "&"));
        }

        std::string canonicalQueryStringUrl(const std::string& encodedQueryString)
        {
            std::vector<std::pair<std::string, std::string>> encodedPairs;
            std::vector<std::string> segments = s3::utils::StringUtils::Split(encodedQueryString, '&');
            for (const std::string& seg : segments)
            {
                if (seg.empty())
                {
                    continue;
                }
                std::vector<std::string> kv = s3::utils::StringUtils::Split(seg, '=', 2);
                std::string key = (kv.size() >= 1) ? kv[0] : "";
                std::string val = (kv.size() >= 2) ? kv[1] : "";
                if (key.empty())
                {
                    continue;
                }
                encodedPairs.push_back(std::make_pair(key, val));
            }

            return canonicalQueryStringByVecPair(encodedPairs);
        }

        std::string signedHeaders(const std::vector<std::pair<std::string, std::string>>& headersToSign)
        {
            std::unordered_set<std::string> uniqueSet;
            for (const auto& kv : headersToSign)
            {
                std::string lowerKey = s3::utils::StringUtils::ToLower(kv.first.c_str());
                std::string trimmedKey = s3::utils::StringUtils::Trim(lowerKey.c_str());
                uniqueSet.insert(trimmedKey);
            }

            std::vector<std::string> headersVec;
            headersVec.reserve(uniqueSet.size());
            for (const std::string& key : uniqueSet)
            {
                headersVec.push_back(key);
            }
            std::sort(headersVec.begin(), headersVec.end(), std::less<std::string>());
            return fmt::to_string(fmt::join(headersVec, ";"));
        }

        std::vector<std::pair<std::string, std::string>> headersToSign(const std::vector<std::pair<std::string, std::string>>& headers)
        {
            static const std::unordered_set<std::string> signedHeadersBlacklist = {
                "connection",        "expect",  "keep-alive", "proxy-authenticate", "proxy-authorization", "te", "trailer",
                "transfer-encoding", "upgrade", "user-agent", "x-amzn-trace-id",
            };
            std::vector<std::pair<std::string, std::string>> headerMap;
            for (const auto& kv : headers)
            {
                const std::string& key = kv.first;
                const std::string& value = kv.second;
                std::string lowerKey = s3::utils::StringUtils::ToLower(key.c_str());
                if (signedHeadersBlacklist.find(lowerKey) == signedHeadersBlacklist.end())
                {
                    headerMap.emplace_back(lowerKey, value);
                }
            }
            return headerMap;
        }

        std::pair<std::string, std::string> makeAuthorizationHeaderKv(const std::string& scope, const std::string& signedHeaders,
                                                                      const std::string& signature)
        {
            std::vector<std::string> vec{
                fmt::format("AWS4-HMAC-SHA256 Credential={}", scope),
                fmt::format("SignedHeaders={}", signedHeaders),
                fmt::format("Signature={}", signature),
            };
            std::string value = fmt::to_string(fmt::join(vec, ", "));
            return std::make_pair("Authorization", value);
        }
    } // namespace auth
} // namespace s3