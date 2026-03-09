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

    OptStr::OptStr() : _hasVal(false), _val() {}

    OptStr::OptStr(const std::string& val) : _hasVal(true), _val(val) {}

    OptStr::OptStr(std::string&& val) : _hasVal(true), _val(std::move(val)) {}

    OptStr& OptStr::operator=(const std::string& val)
    {
        _hasVal = true;
        _val = val;
        return *this;
    }

    OptStr& OptStr::operator=(std::string&& val)
    {
        _hasVal = true;
        _val = std::move(val);
        return *this;
    }

    bool OptStr::has() const
    {
        return _hasVal;
    }

    const std::string& OptStr::value() const
    {
        return _val;
    }
    std::string& OptStr::value()
    {
        return _val;
    }

    void OptStr::reset()
    {
        _hasVal = false;
        _val.clear();
    }
} // namespace s3