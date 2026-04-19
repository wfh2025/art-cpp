#include "s3_auth.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "openssl/evp.h"
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
        /**
         * 计算canonicalHeaders
         * @param headers http头
         */
        std::string canonicalHeaders(const std::vector<std::pair<std::string, std::string>>& headers)
        {
            // caution: 存在大小写不同的header，例如: host/Host
            // caution: grouped的顺序
            std::map<std::string, std::vector<std::string>, std::less<std::string>> grouped;
            for (const auto& kv : headers)
            {
                std::string lowerKey = kv.first;
                std::transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), [](unsigned char c) { return std::tolower(c); });
                std::string processed = ensureUnicode(headerValue(kv.second));
                grouped[lowerKey].push_back(processed);
            }

            std::vector<std::string> lines;
            for (const auto& entry : grouped)
            {
                const std::string& key = entry.first;
                const auto& values = entry.second;

                std::string joined_values = fmt::to_string(fmt::join(values, ","));
                lines.push_back(fmt::format("{}:{}", key, joined_values));
            }
            return fmt::to_string(fmt::join(lines, "\n"));
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

    } // namespace auth
} // namespace s3