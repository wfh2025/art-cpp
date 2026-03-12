#include "s3_base.hpp"

#include "spdlog/spdlog.h"
namespace s3
{
    namespace base
    {
        OptInt64::OptInt64() : _has(false), _val(0)
        {
            SPDLOG_DEBUG("fn: OptInt64(), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }

        OptInt64::OptInt64(int64_t val) : _has(true), _val(val)
        {
            SPDLOG_DEBUG("fn: OptInt64(int64_t val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }

        OptInt64::~OptInt64()
        {
            SPDLOG_DEBUG("fn: ~OptInt64(), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }

        OptInt64& OptInt64::operator=(int64_t val)
        {
            _has = true;
            _val = val;
            SPDLOG_DEBUG("fn: OptInt64& operator=(int64_t val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
            return *this;
        }

        bool OptInt64::has() const
        {
            return _has;
        }

        int64_t OptInt64::value() const
        {
            return _val;
        }

        void OptInt64::reset()
        {
            _has = false;
            _val = 0;
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

    } // namespace base
}; // namespace s3