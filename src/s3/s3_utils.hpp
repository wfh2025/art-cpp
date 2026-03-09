#pragma once
#include <chrono>
#include <cstdint>
#include <string>

namespace s3
{
    std::string timeToISO8601(const std::chrono::system_clock::time_point& time);

    class OptStr
    {
    public:
        OptStr();
        OptStr(const std::string& val);
        OptStr(std::string&& val);
        OptStr& operator=(const std::string& val);
        OptStr& operator=(std::string&& val);
        ~OptStr();
        bool has() const;
        const std::string& value() const;
        std::string& value();
        void reset();

    private:
        bool _hasVal;
        std::string _val;
    };
} // namespace s3
