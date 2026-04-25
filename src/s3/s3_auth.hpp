#pragma once

#include <cstdint>
#include <map>
#include <string>

#include "s3_base.hpp"

namespace s3
{
    namespace auth
    {
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

    } // namespace auth
} // namespace s3