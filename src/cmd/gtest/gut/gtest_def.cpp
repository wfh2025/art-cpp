#include "gtest_def.hpp"

#include <utility>

#include "fmt/core.h"
#include "spdlog/spdlog.h"

namespace gut
{
    Point2i::Point2i() : Point2i(0, 0)
    {
        /* 无参构造函数 */
        SPDLOG_INFO("Point2i(), this: {}, x: {}, y: {}", fmt::ptr(this), _x, _y);
    }
    Point2i::Point2i(int x, int y) : _x(x), _y(y)
    {
        /* 带参构造函数 */
        SPDLOG_INFO("Point2i(int x, int y), this: {}, x: {}, y: {}", fmt::ptr(this), _x, _y);
    }

    Point2i::Point2i(const std::pair<int, int>& values) : _x(values.first), _y(values.second)
    {
        /* 转换构造函数 */
        SPDLOG_INFO("Point2i(const std::pair<int, int>& values), this: {}, x: {}, y: {}", fmt::ptr(this), _x, _y);
    }

    Point2i::Point2i(const Point2i& other) : _x(other._x), _y(other._y)
    {
        SPDLOG_INFO("Point2i(const Point2i& other), "
                    "this: {}, this->x: {}, this->y: {}, "
                    "other: {}, other.x: {}, other.y: {}",
                    fmt::ptr(this), this->_x, this->_y, fmt::ptr(&other), other._x, other._y);
    }

    Point2i::Point2i(Point2i&& other) noexcept : _x(other._x), _y(other._y)
    {
        /* 移动构造函数 */
        other._x = -1;
        other._y = -1;
        SPDLOG_INFO("Point2i(Point2i&& other), "
                    "this: {}, this->x: {}, this->y: {}, "
                    "other: {}, other.x: {}, other.y: {}",
                    fmt::ptr(this), this->_x, this->_y, fmt::ptr(&other), other._x, other._y);
    }

    Point2i& Point2i::operator=(const Point2i& other)
    {
        if (this != &other)
        {
            this->_x = other._x;
            this->_y = other._y;
        }

        SPDLOG_INFO("Point2i& operator=(const Point2i& other), "
                    "this: {}, this->x: {}, this->y: {}, "
                    "other: {}, other.x: {}, other.y: {} ",
                    fmt::ptr(this), this->_x, this->_y, fmt::ptr(&other), other._x, other._y);
        return *this;
    }
    Point2i& Point2i::operator=(Point2i&& other) noexcept
    {
        if (this != &other)
        {
            this->_x = other._x;
            this->_y = other._y;
            other._x = -1;
            other._y = -1;
        }

        SPDLOG_INFO("Point2i& operator=(Point2i&& other), "
                    "this: {}, this->x: {}, this->y: {}, "
                    "other: {}, other.x: {}, other.y: {}",
                    fmt::ptr(this), this->_x, this->_y, fmt::ptr(&other), other._x, other._y);
        return *this;
    }

    Point2i::~Point2i()
    {
        SPDLOG_INFO("~Point2i(), this: {}, x: {}, y: {}", fmt::ptr(this), _x, _y);
    }

    X::X() : _val(0)
    {
        SPDLOG_INFO("fn: X(), this: {}, val: {}", fmt::ptr(this), _val);
    }

    X::X(int v) : _val(v)
    {
        SPDLOG_INFO("fn: X(int v), this: {}, val: {}", fmt::ptr(this), _val);
    }

    X::X(const X& other)
    {
        SPDLOG_INFO("fn: X(const X& other), this: {}, other: {}", fmt::ptr(this), fmt::ptr(&other));
    }

    X::X(X&& other) : _val(other._val)
    {
        SPDLOG_INFO("fn: X(X&& other), this: {}, other: {}", fmt::ptr(this), fmt::ptr(&other));
    }

    X& X::operator=(const X& other)
    {
        SPDLOG_INFO("fn: X& operator=(const X& other), this: {}, other: {}", fmt::ptr(this), fmt::ptr(&other));
        return *this;
    }

    X& X::operator=(X&& other)
    {
        SPDLOG_INFO("fn: X& operator=(X&& other), this: {}, other: {}", fmt::ptr(this), fmt::ptr(&other));
        return *this;
    }

    X::~X()
    {
        SPDLOG_INFO("fn: ~X(), this: {}, val: {}", fmt::ptr(this), _val);
    }

    Y::Y() : _val(0)
    {
        SPDLOG_INFO("fn: Y(), this: {}, val: {}", fmt::ptr(this), _val);
    }

    Y::Y(int v) : _val(v)
    {
        SPDLOG_INFO("fn: Y(int v), this: {}, val: {}", fmt::ptr(this), _val);
    }

    Y::Y(const Y& other) : _val(other._val)
    {
        SPDLOG_INFO("fn: Y(const Y& other), this: {}, other: {}", fmt::ptr(this), fmt::ptr(&other));
    }

    Y::Y(Y&& other) : _val(other._val)
    {
        SPDLOG_INFO("fn: Y(Y&& other), this: {}, other: {}", fmt::ptr(this), fmt::ptr(&other));
    }

    Y& Y::operator=(const Y& other)
    {
        SPDLOG_INFO("fn: Y& operator=(const Y& other), this: {}, other: {}", fmt::ptr(this), fmt::ptr(&other));
        return *this;
    }

    Y& Y::operator=(Y&& other)
    {
        SPDLOG_INFO("fn: Y& operator=(Y&& other), this: {}, other: {}", fmt::ptr(this), fmt::ptr(&other));
        return *this;
    }

    Y::~Y()
    {
        SPDLOG_INFO("fn: ~Y(), this: {}, val: {}", fmt::ptr(this), _val);
    }

} // namespace gut