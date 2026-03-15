#include "s3_base.hpp"

#include "spdlog/spdlog.h"
namespace s3
{
    namespace base
    {
        OptI32::OptI32() noexcept : _has(false), _val(0)
        {
            SPDLOG_DEBUG("fn: OptI32(), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }
        OptI32::OptI32(int32_t val) noexcept : _has(true), _val(val)
        {
            SPDLOG_DEBUG("fn: OptI32(int32_t val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }

        OptI32::~OptI32() noexcept
        {
            SPDLOG_DEBUG("fn: ~OptI32(), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }

        OptI32& OptI32::operator=(int32_t val) noexcept
        {
            _has = true;
            _val = val;
            SPDLOG_DEBUG("fn: OptI32& operator=(int32_t val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
            return *this;
        }

        bool OptI32::has() const noexcept
        {
            return _has;
        }

        int32_t OptI32::value() const noexcept
        {
            return _val;
        }

        void OptI32::reset() noexcept
        {
            _has = false;
            _val = 0;
        }

        OptI64::OptI64() noexcept : _has(false), _val(0)
        {
            SPDLOG_DEBUG("fn: OptI64(), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }
        OptI64::OptI64(int64_t val) noexcept : _has(true), _val(val)
        {
            SPDLOG_DEBUG("fn: OptI64(int64_t val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }

        OptI64::~OptI64() noexcept
        {
            SPDLOG_DEBUG("fn: ~OptI64(), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
        }

        OptI64& OptI64::operator=(int64_t val) noexcept
        {
            _has = true;
            _val = val;
            SPDLOG_DEBUG("fn: OptI64& operator=(int64_t val), this: {}, has: {}, val: {}, &val: {}", fmt::ptr(this), _has, _val, fmt::ptr(&_val));
            return *this;
        }

        bool OptI64::has() const noexcept
        {
            return _has;
        }

        int64_t OptI64::value() const noexcept
        {
            return _val;
        }

        void OptI64::reset() noexcept
        {
            _has = false;
            _val = 0;
        }

        OptStr::OptStr() noexcept : _has(false), _val()
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

        const std::string& OptStr::value() const noexcept
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