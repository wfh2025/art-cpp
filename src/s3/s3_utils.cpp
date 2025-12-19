#include "s3_utils.hpp"

#include <iomanip>
#include <sstream>

namespace s3
{
    std::string timeToISO8601(const std::chrono::system_clock::time_point& time)
    {
        auto t = std::chrono::system_clock::to_time_t(time);
        auto tm = std::gmtime(&t);
        return (std::stringstream() << std::put_time(tm, "%Y-%m-%dT%H:%M:%S.000Z")).str();
    }
} // namespace s3