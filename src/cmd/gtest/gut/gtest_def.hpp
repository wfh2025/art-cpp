#ifndef GTEST_DEF_HPP_INCLUDED
#define GTEST_DEF_HPP_INCLUDED

#include <utility>

namespace gut
{
    class Point2i
    {
    public:
        Point2i();
        Point2i(int x, int y);
        Point2i(const std::pair<int, int>& values);
        Point2i(const Point2i& other);
        Point2i(Point2i&& other) noexcept;
        Point2i& operator=(const Point2i& other);
        Point2i& operator=(Point2i&& other) noexcept;
        ~Point2i();

    public:
        int _x;
        int _y;
    };
}; // namespace gut

#endif