#ifndef ART_S3_S3_UTILS_HPP_INCLUDED
#define ART_S3_S3_UTILS_HPP_INCLUDED
#include <chrono>
#include <string>

namespace s3
{
    std::string timeToISO8601(const std::chrono::system_clock::time_point& time);
}
#endif