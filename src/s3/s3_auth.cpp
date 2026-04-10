#include "s3_auth.hpp"

#include <array>
#include <cstdint>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "openssl/err.h"
#include "openssl/evp.h"
#include "openssl/evperr.h"
#include "openssl/hmac.h"
#include "openssl/md5.h"
#include "openssl/sha.h"
#include "s3_base.hpp"
#include "s3_utils.hpp"
#include "spdlog/spdlog.h"

namespace
{
    const char* kEmptySHA256Hash = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    const int64_t kPayloadBuffer = 1024 * 1024;
    const std::unordered_set<std::string> kSignedHeadersBlacklist = {
        "connection",        "expect",  "keep-alive", "proxy-authenticate", "proxy-authorization", "te", "trailer",
        "transfer-encoding", "upgrade", "user-agent", "x-amzn-trace-id",
    };
    const std::string kUnsignedPayload = "UNSIGNED-PAYLOAD";
    const std::string kStreamingUnsignedPayloadTrailer = "STREAMING-UNSIGNED-PAYLOAD-TRAILER";
} // namespace

namespace
{
    s3::base::OptStr sha256HashRawInternal(const std::string& str)
    {
        unsigned char hash[EVP_MAX_MD_SIZE] = {0};
        unsigned int hashLen = 0;

        std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> ctx(EVP_MD_CTX_new(), &EVP_MD_CTX_free);
        if (!ctx)
        {
            return s3::base::OptStr();
        }
        // OpenSSL EVP APIs convention: return 1 on success, otherwise failure.
        if (EVP_DigestInit_ex(ctx.get(), EVP_sha256(), nullptr) != 1)
        {
            return s3::base::OptStr();
        }
        if (EVP_DigestUpdate(ctx.get(), str.data(), str.size()) != 1)
        {
            return s3::base::OptStr();
        }
        if (EVP_DigestFinal_ex(ctx.get(), hash, &hashLen) != 1)
        {
            return s3::base::OptStr();
        }
        return s3::base::OptStr(std::string(reinterpret_cast<const char*>(hash), hashLen));
    }

    s3::base::OptStr hmacSha256RawInternal(const std::string& key, const std::string& data)
    {
        unsigned char mac[EVP_MAX_MD_SIZE] = {0};
        unsigned int macLen = 0;
        unsigned char* ok = HMAC(EVP_sha256(), key.data(), static_cast<int>(key.size()), reinterpret_cast<const unsigned char*>(data.data()),
                                 data.size(), mac, &macLen);
        if (ok == nullptr)
        {
            return s3::base::OptStr();
        }
        return s3::base::OptStr(std::string(reinterpret_cast<const char*>(mac), macLen));
    }

    std::string toHexLower(const unsigned char* data, unsigned int len)
    {
        std::ostringstream oss;
        for (unsigned int i = 0; i < len; ++i)
        {
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];
        }
        return oss.str();
    }
} // namespace

namespace s3
{
    namespace auth
    {
        s3::base::OptStr sha256HashHex(const std::string& data)
        {
            const s3::base::OptStr raw = sha256HashRawInternal(data);
            if (!raw.has())
            {
                return s3::base::OptStr();
            }
            const std::string& bytes = raw.value();
            return s3::base::OptStr(toHexLower(reinterpret_cast<const unsigned char*>(bytes.data()), static_cast<unsigned int>(bytes.size())));
        }

        s3::base::OptStr hmacSha256Hex(const std::string& key, const std::string& data)
        {
            const s3::base::OptStr raw = hmacSha256RawInternal(key, data);
            if (!raw.has())
            {
                return s3::base::OptStr();
            }
            const std::string& bytes = raw.value();
            return s3::base::OptStr(toHexLower(reinterpret_cast<const unsigned char*>(bytes.data()), static_cast<unsigned int>(bytes.size())));
        }

        std::string buildScope(const std::string& accessKeyId, const std::string& date, const std::string& region, const std::string& service)
        {
            // ref: https://docs.aws.amazon.com/AmazonS3/latest/API/sigv4-auth-using-authorization-header.html
            // fn: scope
            // format: <your-access-key-id>/<date>/<aws-region>/<aws-service>/aws4_request
            // <date>: YYYYMMDD
            // <service>: s3
            return fmt::format("{}/{}/{}/{}/aws4_request", accessKeyId, date, region, service);
        }

        std::string buildCredentialScope(const std::string& date, const std::string& region, const std::string& service)
        {
            // ref: https://github.com/boto/botocore/blob/develop/botocore/auth.py
            // fn: credential_scope
            return fmt::format("{}/{}/{}/aws4_request", date, region, service);
        }

        std::string buildCanonicalRequest(const std::string& httpMethod, const std::string& canonicalUri, const std::string& canonicalQueryString,
                                          const std::string& canonicalHeaders, const std::string& signedHeaders, const std::string& hashedPayload)
        {
            return fmt::format("{}\n{}\n{}\n{}\n{}\n{}", s3::utils::StringUtils::ToUpper(httpMethod.c_str()), canonicalUri, canonicalQueryString,
                               canonicalHeaders, signedHeaders, hashedPayload);
        }

        // caution: queryMap均未编码
        std::string buildCanonicalQueryString(const std::map<std::string, std::string>& queryMap)
        {
            // 按“编码后 key，再编码后 value”排序
            std::vector<std::pair<std::string, std::string>> encodedPairs;
            encodedPairs.reserve(queryMap.size());
            for (const auto& kv : queryMap)
            {
                encodedPairs.emplace_back(s3::utils::StringUtils::URLEncode(kv.first), s3::utils::StringUtils::URLEncode(kv.second));
            }
            std::sort(encodedPairs.begin(), encodedPairs.end(),
                      [](const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {
                          if (a.first != b.first)
                          {
                              return a.first < b.first;
                          }
                          return a.second < b.second;
                      });
            std::string canonical = "";
            for (size_t i = 0; i < encodedPairs.size(); ++i)
            {
                if (i > 0)
                {
                    canonical.push_back('&');
                }
                canonical += encodedPairs[i].first;
                canonical.push_back('=');
                canonical += encodedPairs[i].second;
            }
            return canonical;
        }

        // caution: headers是来自http的头，未做任何修改
        std::string buildCanonicalHeaders(const std::map<std::string, std::string>& headers)
        {
            // ref: https://docs.aws.amazon.com/AmazonS3/latest/API/sig-v4-header-based-auth.html
            // CanonicalHeaders: lowercase(header-name) + ":" + Trim(value) + "\n"
            // Keep canonical header names sorted in ascending lexical order.
            std::map<std::string, std::string, std::less<std::string>> normalized;
            for (const auto& kv : headers)
            {
                const std::string lowerName = s3::utils::StringUtils::ToLower(kv.first.c_str());
                const std::string trimmedValue = s3::utils::StringUtils::Trim(kv.second.c_str());

                // If callers provide case-variant duplicates (e.g. Host + host),
                // merge them into one canonical key in insertion order.
                std::map<std::string, std::string>::iterator it = normalized.find(lowerName);
                if (it == normalized.end())
                {
                    normalized.emplace(lowerName, trimmedValue);
                }
                else
                {
                    if (!it->second.empty())
                    {
                        it->second.push_back(',');
                    }
                    it->second += trimmedValue;
                }
            }

            std::string canonical = "";
            for (const auto& kv : normalized)
            {
                canonical += kv.first;
                canonical.push_back(':');
                canonical += kv.second;
                canonical.push_back('\n');
            }
            return canonical;
        }

    } // namespace auth
} // namespace s3