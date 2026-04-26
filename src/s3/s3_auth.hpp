#pragma once

#include <cstdint>
#include <map>
#include <string>

#include "s3_base.hpp"

namespace s3
{
    namespace auth
    {
        struct S3AuthRequest
        {
            std::string timestamp;                                        // '20260425T092048Z'
            std::string upperHttpMethod;                                  // 大写的HTTP方法
            std::string path;                                             // http请求路径
            std::string canoicalQueryString;                              // 标准化查询字符串
            std::vector<std::pair<std::string, std::string>> headers;     // 头
            std::vector<std::pair<std::string, std::string>> queryParams; // 查询参数
            std::string accessKey;
            std::string secretKey;
            std::string regionName;
            std::string serviceName;
        };

        extern const std::string kUnsignedPayload;
        extern const std::string kStreamingUnsignedPayloadTrailer;
        extern const std::string kEmptySha256Hash;

        enum class SignatureVersion : int32_t
        {
            Unknown,
            V2,
            V3,
            V3Https,
            S3,
            S3Query,
            S3PresignPost,
            S3V4PresignPost,
            V4S3Express,
            V4S3ExpressQuery,
            V4S3ExpressPresignPost,
            Bearer,
            V4,
            V4Query,
            S3V4,
            S3V4Query,
            V4a,
            S3V4a,
            S3V4aQuery,
        };

        const char* signatureVersionToString(SignatureVersion v) noexcept;

        SignatureVersion stringToSignatureVersion(const std::string& s) noexcept;

        std::string scope(const std::string& accessKey, const std::string& timestamp, const std::string& regionName, const std::string& serviceName);

        /**
         * @param secretKey
         * @param dateStamp
         * @param regionName
         * @param serviceName
         * @param stringToSign
         */
        std::string signature(const std::string& secretKey, const std::string& dateStamp, const std::string& regionName,
                              const std::string& serviceName, const std::string& stringToSign);

        std::pair<std::string, std::string> makeAuthorizationHeaderKv(const std::string& scope, const std::string& signedHeaders,
                                                                      const std::string& signature);
        std::vector<std::pair<std::string, std::string>> headersToSign(const std::vector<std::pair<std::string, std::string>>& headers);
        std::string signedHeaders(const std::vector<std::pair<std::string, std::string>>& headersToSign);
        std::string canonicalQueryStringUrl(const std::string& encodedQueryString);
        std::string canonicalQueryStringByVecPair(std::vector<std::pair<std::string, std::string>>& encodedPairs);
        std::string canonicalRequest(const std::string& upperHttpMethod, const std::string& normalizedUrlPath,
                                     const std::string& canonicalQueryString, const std::string& canonicalHeaders, const std::string& signedHeaders,
                                     const std::string& bodyChecksum);
        std::string stringToSign(const std::string& timestamp, const std::string& credentialScope, const std::string& canonicalRequest);
        std::string credentialScope(const std::string& dateStamp, const std::string& regionName, const std::string& serviceName);
        std::string canonicalHeaders(const std::vector<std::pair<std::string, std::string>>& headersToSign);
        std::string percentDecode(const char* safe);
        std::string percentEncode(const std::string& input, const std::string& safe);

    } // namespace auth
} // namespace s3