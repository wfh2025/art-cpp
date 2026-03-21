#pragma once
#include <chrono>
#include <cstdint>
#include <string>

namespace s3
{
    namespace utils
    {
        std::string timeToISO8601(const std::chrono::system_clock::time_point& time);
    }

} // namespace s3
