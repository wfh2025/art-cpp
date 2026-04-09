#include "s3_auth.hpp"

#include <array>
#include <cstdint>
#include <iomanip>
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
    std::string sha256(const std::string& str)
    {
        unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
        SHA256_CTX ctx;
        SHA256_Init(&ctx);
        SHA256_Update(&ctx, str.c_str(), str.size());
        SHA256_Final(hash, &ctx);

        std::ostringstream oss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }
        return oss.str();
        return "";
    }
} // namespace

namespace s3
{
    namespace auth
    {
        // ref: https://docs.aws.amazon.com/AmazonS3/latest/API/sig-v4-header-based-auth.html
        std::string uriEncode(const std::string& src)
        {
            static const std::unordered_set<char> kUnreservedChars = {
                '-',
                '_',
                '.',
                '~',
            };
            static constexpr char kHex[] = "0123456789ABCDEF";
            const auto isAsciiAlnum = [](unsigned char c) { return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'); };
            std::string out;
            out.reserve(src.size() * 3);

            for (const unsigned char c : src)
            {
                bool shouldEncode = true;
                if (isAsciiAlnum(c) || c == '/')
                {
                    shouldEncode = false;
                }
                else
                {
                    shouldEncode = (kUnreservedChars.find(static_cast<char>(c)) == kUnreservedChars.end());
                }
                if (!shouldEncode)
                {
                    out.push_back(static_cast<char>(c));
                    continue;
                }
                out.push_back('%');
                out.push_back(kHex[(c >> 4) & 0x0F]);
                out.push_back(kHex[c & 0x0F]);
            }
            return out;
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
    } // namespace auth
} // namespace s3