#include "gtest_def.hpp"

#include <utility>

#include "fmt/core.h"
#include "spdlog/spdlog.h"

namespace gut
{
    Point2i::Point2i() : Point2i(0, 0)
    {
        /* 无参构造函数 */
        SPDLOG_INFO("Point2i::Point2i(), x: {}, y: {}, &x: {}, &y: {}", _x, _y, fmt::ptr(&_x), fmt::ptr(&_y));
    }
    Point2i::Point2i(int x, int y) : _x(x), _y(y)
    {
        /* 带参构造函数 */
        SPDLOG_INFO("Point2i::Point2i(int x, int y), x: {}, y: {}, &x: {}, &y: {}", _x, _y, fmt::ptr(&_x), fmt::ptr(&_y));
    }

    Point2i::Point2i(const std::pair<int, int>& values) : _x(values.first), _y(values.second)
    {
        /* 转换构造函数 */
        SPDLOG_INFO("Point2i::Point2i(const std::pair<int, int>& values), x: {}, y: {}, &x: {}, &y: {}", _x, _y, fmt::ptr(&_x), fmt::ptr(&_y));
    }

    Point2i::Point2i(const Point2i& other) : _x(other._x), _y(other._y)
    {
        SPDLOG_INFO("Point2i::Point2i(const Point2i& other), "
                    "this->x: {}, this->y: {}, &this->x: {}, &this->y: {}, "
                    "&(other._x): {}, &(other._y): {}",
                    this->_x, this->_y, fmt::ptr(&this->_x), fmt::ptr(&this->_y), fmt::ptr(&other._x), fmt::ptr(&other._y));
    }

    Point2i::Point2i(Point2i&& other) noexcept : _x(other._x), _y(other._y)
    {
        /* 移动构造函数 */
        other._x = -1;
        other._y = -1;
        SPDLOG_INFO("Point2i::Point2i(Point2i&& other) noexcept, "
                    "this->x: {}, this->y: {}, &this->x: {}, &this->y: {}, "
                    "other._x: {}, other._y: {}, "
                    "&(other._x): {}, &(other._y): {}",
                    this->_x, this->_y, fmt::ptr(&this->_x), fmt::ptr(&this->_y), other._x, other._y, fmt::ptr(&other._x), fmt::ptr(&other._y));
    }

    Point2i& Point2i::operator=(const Point2i& other)
    {
        if (this != &other)
        {
            this->_x = other._x;
            this->_y = other._y;
        }

        SPDLOG_INFO("Point2i& Point2i::operator=(const Point2i& other), "
                    "this->x: {}, this->y: {}, &this->x: {}, &this->y: {}, "
                    "other._x: {}, other._y: {}, "
                    "&(other._x): {}, &(other._y): {}",
                    this->_x, this->_y, fmt::ptr(&this->_x), fmt::ptr(&this->_y), other._x, other._y, fmt::ptr(&other._x), fmt::ptr(&other._y));
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

        SPDLOG_INFO("Point2i& Point2i::operator=(Point2i&& other) noexcept, "
                    "this->x: {}, this->y: {}, &this->x: {}, &this->y: {}, "
                    "other._x: {}, other._y: {}, "
                    "&(other._x): {}, &(other._y): {}",
                    this->_x, this->_y, fmt::ptr(&this->_x), fmt::ptr(&this->_y), other._x, other._y, fmt::ptr(&other._x), fmt::ptr(&other._y));
        return *this;
    }

    Point2i::~Point2i()
    {
        SPDLOG_INFO("Point2i::~Point2i(), x: {}, y: {}, &x: {}, &y: {}", _x, _y, fmt::ptr(&_x), fmt::ptr(&_y));
    }
} // namespace gut