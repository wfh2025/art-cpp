#include "s3_base.hpp"

#include "spdlog/spdlog.h"
namespace s3
{
    namespace base
    {
        OptInt32::OptInt32() noexcept : _has(false), _val(0)
        {
            SPDLOG_DEBUG("fn: OptInt32(), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }
        OptInt32::OptInt32(int32_t val) noexcept : _has(true), _val(val)
        {
            SPDLOG_DEBUG("fn: OptInt32(int32_t val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }

        OptInt32::~OptInt32() noexcept
        {
            SPDLOG_DEBUG("fn: ~OptInt32(), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }

        OptInt32& OptInt32::operator=(int32_t val) noexcept
        {
            _has = true;
            _val = val;
            SPDLOG_DEBUG("fn: OptInt32& operator=(int32_t val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
            return *this;
        }

        bool OptInt32::has() const noexcept
        {
            return _has;
        }

        int32_t OptInt32::value() const noexcept
        {
            return _val;
        }

        void OptInt32::reset() noexcept
        {
            _has = false;
            _val = 0;
        }

        OptInt64::OptInt64() noexcept : _has(false), _val(0)
        {
            SPDLOG_DEBUG("fn: OptInt64(), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }
        OptInt64::OptInt64(int64_t val) noexcept : _has(true), _val(val)
        {
            SPDLOG_DEBUG("fn: OptInt64(int64_t val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }

        OptInt64::~OptInt64() noexcept
        {
            SPDLOG_DEBUG("fn: ~OptInt64(), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }

        OptInt64& OptInt64::operator=(int64_t val) noexcept
        {
            _has = true;
            _val = val;
            SPDLOG_DEBUG("fn: OptInt64& operator=(int64_t val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
            return *this;
        }

        bool OptInt64::has() const noexcept
        {
            return _has;
        }

        int64_t OptInt64::value() const noexcept
        {
            return _val;
        }

        void OptInt64::reset() noexcept
        {
            _has = false;
            _val = 0;
        }

        OptStr::OptStr() : _has(false), _val()
        {
            SPDLOG_DEBUG("fn: OptStr(), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(_val.data()));
        }

        OptStr::OptStr(const char* s) : _has(s != nullptr), _val((s != nullptr) ? s : "")
        {
            SPDLOG_DEBUG("fn: OptStr(const char* s), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(_val.data()));
        }

        OptStr::OptStr(const std::string& val) : _has(true), _val(val)
        {
            SPDLOG_DEBUG("fn: OptStr(const std::string& val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val,
                         fmt::ptr(_val.data()));
        }
        OptStr::OptStr(std::string&& val) : _has(true), _val(std::move(val))
        {
            SPDLOG_DEBUG("fn: OptStr(std::string&& val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(_val.data()));
        }

        OptStr& OptStr::operator=(const std::string& val)
        {
            _has = true;
            _val = val;
            SPDLOG_DEBUG("fn: OptStr& operator=(const std::string& val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val,
                         fmt::ptr(_val.data()));
            return *this;
        }

        OptStr& OptStr::operator=(const char* s)
        {
            if (s != nullptr)
            {
                _has = true;
                _val = s;
            }
            else
            {
                reset();
            }
            SPDLOG_DEBUG("fn: OptStr& operator=(const char* s), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val,
                         fmt::ptr(_val.data()));
            return *this;
        }

        OptStr& OptStr::operator=(std::string&& val)
        {
            _has = true;
            _val = std::move(val);
            SPDLOG_DEBUG("fn: OptStr& operator=(std::string&& val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val,
                         fmt::ptr(_val.data()));
            return *this;
        }

        bool OptStr::has() const noexcept
        {
            return _has;
        }

        const std::string& OptStr::value() const
        {
            return _val;
        }

        void OptStr::reset() noexcept
        {
            _has = false;
            _val.clear();
        }
        OptStr::~OptStr() noexcept
        {
            SPDLOG_DEBUG("fn: ~OptStr(), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(_val.data()));
        }
    } // namespace base
} // namespace s3