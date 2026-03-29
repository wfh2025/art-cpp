#include "s3_utils.hpp"

#include <iomanip>
#include <sstream>

namespace s3
{
    namespace utils
    {
        bool isNullOrEmpty(const char* s)
        {
            return s == nullptr || s[0] == '\0';
        }

        s3::base::OptI64 parseInt64(const char* s)
        {
            if (isNullOrEmpty(s))
            {
                return s3::base::OptI64{};
            }
            return parseInt64(std::string(s));
        }

        std::string timeToISO8601(const std::chrono::system_clock::time_point& time)
        {
            auto t = std::chrono::system_clock::to_time_t(time);
            auto tm = std::gmtime(&t);
            return (std::stringstream() << std::put_time(tm, "%Y-%m-%dT%H:%M:%S.000Z")).str();
        }

        s3::base::OptI64 parseInt64(const std::string& str)
        {
            s3::base::OptI64 optVal;
            int64_t tmp = 0;
            std::size_t pos = 0;
            try
            {
                tmp = std::stoll(str, &pos, 10);
            }
            catch (...)
            {
                return optVal;
            }
           
            if (pos != str.size())
            {
                return optVal;
            }
            optVal = tmp;
            return optVal;
        }
    } // namespace utils
} // namespace s3