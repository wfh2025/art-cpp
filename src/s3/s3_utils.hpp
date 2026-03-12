#pragma once
#include <chrono>
#include <cstdint>
#include <string>

namespace s3
{
    std::string timeToISO8601(const std::chrono::system_clock::time_point& time);

} // namespace s3
