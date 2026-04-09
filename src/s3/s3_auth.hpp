#pragma once

#include <cstdint>
#include <string>

namespace s3
{
    namespace auth
    {
        std::string uriEncode(const std::string& src);
        std::string buildScope(const std::string& accessKeyId, const std::string& date, const std::string& region, const std::string& service);
        std::string buildCredentialScope(const std::string& date, const std::string& region, const std::string& service);
    } // namespace auth
} // namespace s3