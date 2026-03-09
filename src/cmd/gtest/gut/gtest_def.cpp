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
} // namespace gut