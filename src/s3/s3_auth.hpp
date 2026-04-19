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

    } // namespace auth
} // namespace s3