#pragma once

#include <cstdint>
#include <map>
#include <string>

#include "s3_base.hpp"

namespace s3
{
    namespace auth
    {
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