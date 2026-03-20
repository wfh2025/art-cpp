#include "s3_base.hpp"

#include "spdlog/spdlog.h"
namespace s3
{
    namespace base
    {
        OptBool::OptBool() noexcept : _has(false), _val(false) {}

        OptBool::OptBool(bool val) noexcept : _has(true), _val(val) {}

        OptBool::~OptBool() noexcept {}

        OptBool& OptBool::operator=(bool val) noexcept
        {
            _has = true;
            _val = val;
            return *this;
        }

        bool OptBool::has() const noexcept
        {
            return _has;
        }

        bool OptBool::value() const noexcept
        {
            return _val;
        }

        void OptBool::reset() noexcept
        {
            _has = false;
            _val = false;
        }

        OptI32::OptI32() noexcept : _has(false), _val(0) {}

        OptI32::OptI32(int32_t val) noexcept : _has(true), _val(val) {}

        OptI32::~OptI32() noexcept {}

        OptI32& OptI32::operator=(int32_t val) noexcept
        {
            _has = true;
            _val = val;
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

        OptF32::OptF32() noexcept : _has(false), _val(0.0f) {}

        OptF32::OptF32(float val) noexcept : _has(true), _val(val) {}

        OptF32::~OptF32() noexcept {}

        OptF32& OptF32::operator=(float val) noexcept
        {
            _has = true;
            _val = val;
            return *this;
        }

        bool OptF32::has() const noexcept
        {
            return _has;
        }

        float OptF32::value() const noexcept
        {
            return _val;
        }

        void OptF32::reset() noexcept
        {
            _has = false;
            _val = 0.0f;
        }

        OptF64::OptF64() noexcept : _has(false), _val(0.0) {}

        OptF64::OptF64(double val) noexcept : _has(true), _val(val) {}

        OptF64::~OptF64() noexcept {}

        OptF64& OptF64::operator=(double val) noexcept
        {
            _has = true;
            _val = val;
            return *this;
        }

        bool OptF64::has() const noexcept
        {
            return _has;
        }

        double OptF64::value() const noexcept
        {
            return _val;
        }

        void OptF64::reset() noexcept
        {
            _has = false;
            _val = 0.0;
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