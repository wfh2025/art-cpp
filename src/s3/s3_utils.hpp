#pragma once
#include <chrono>
#include <cstdint>
#include <string>

#include "s3_base.hpp"

namespace s3
{
    namespace utils
    {
        bool isNullOrEmpty(const char* s);
        s3::base::OptI64 parseInt64(const std::string& str);
        std::string timeToISO8601(const std::chrono::system_clock::time_point& time);

    } // namespace utils

} // namespace s3
