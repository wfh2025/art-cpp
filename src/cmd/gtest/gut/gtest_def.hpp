#pragma once
#include <utility>
namespace gut
{
    class Point2i
    {
    public:
        /**
         * 成功调用:
         * - gut::Point2i pt;
         * - gut::Point2i pt{};
         * - gut::Point2i();
         * - new gut::Point2i();
         * - std::make_shared<gut::Point2i>();
         * - std::make_unique<gut::Point2i>();
         * - 成员初始化列表: var(), 例如下面的pt()
         *   struct X
         *    {
         *      gut::Point2i pt;
         *      X() : pt() {}
         *   };
         *   X x;
         * - 成员初始化列表中未列出的成员,例如下面的pt
         *     struct X
         *     {
         *         gut::Point2i pt;
         *         X() {}
         *     };
         *     X x;
         * - 数组/容器: gut::Point2i arr[n]; std::vector<gut::Point2i> v(n);
         *
         * 失败调用:
         * - gut::Point2i pt();
         */
        Point2i();

        Point2i(int x, int y);
        Point2i(const std::pair<int, int>& values);

        /**
         * 成功调用:
         * - gut::Point2i p0(1, 3); gut::Point2i p1(p0);
         * - gut::Point2i p0(1, 3); gut::Point2i p2 = p0;
         * - gut::Point2i p0(1, 3); auto fn = [](gut::Point2i pt) {}; fn(p0);
         * - 容器: v.push_back(p0); v.emplace_back(p0); m.insert({0, p0})(1次拷贝+1次移动);
         * - vector 用已有对象填充: std::vector<gut::Point2i> v; v.resize(10, p0);
         * - pair/tuple 用已有对象: std::pair<int, gut::Point2i> pr = {0, p0};
         * - 抛出异常: gut::Point2i p(1, 3); throw p;
         * - 按值捕获异常: catch (gut::Point2i p) { ... }
         * - 初始化列表用同类型对象构造成员
         *      struct S { gut::Point2i pt; S(const gut::Point2i& p) : pt(p) {} };
         *      gut::Point2i p0(1, 3); S s(p0);
         * - 数组用已有对象初始化: gut::Point2i arr[] = {p0, p1};
         * - 范围 for 按值: for (gut::Point2i p : vec) { ... }
         *
         * 可能调用:
         * - 按值返回(在允许拷贝/未优化时)
         *      auto fn = []() -> gut::Point2i {
         *          gut::Point2i local(1, 3);
         *          return local;
         *       };
         *       gut::Point2i p = fn();
         */
        Point2i(const Point2i& other);

        /**
         * 成功调用:
         * - gut::Point2i p0(1, 2); gut::Point2i p1 = std::move(p0);
         * - gut::Point2i p0(1, 2); gut::Point2i p1(std::move(p0));
         * - gut::Point2i p0(1, 3); auto fn = [](gut::Point2i pt) {}; fn(std::move(p0));
         * - std::vector<gut::Point2i> v; gut::Point2i p(1, 2); v.push_back(std::move(p));
         * - 初始化成员列表用右值:
         *       struct S
         *       {
         *          gut::Point2i pt;
         *          S(gut::Point2i&& p) : pt(std::move(p)) {}
         *       };
         *       gut::Point2i a(1, 2);
         *       S s(std::move(a));
         *
         * 可能调用:
         * - gut::Point2i p0 = gut::Point2i(1, 2);
         * - auto fn = []() -> gut::Point2i { return gut::Point2i(1, 2); }; fn()
         * - auto fn = [](gut::Point2i pt) {}; fn(gut::Point2i(1, 2));
         * - 按值返回(在允许拷贝/未优化时)
         *      auto fn = []() -> gut::Point2i {
         *          gut::Point2i local(1, 3);
         *          return local;
         *       };
         *       gut::Point2i p = fn();
         *
         */
        Point2i(Point2i&& other) noexcept;

        /**
         * 成功调用:
         * - gut::Point2i p0(1, 2); gut::Point2i p1(3, 4); p1 = p0;
         */
        Point2i& operator=(const Point2i& other);

        /**
         * 成功调用:
         * - gut::Point2i p0(1, 2); gut::Point2i p1(3, 4); p1 = std::move(p0);
         */
        Point2i& operator=(Point2i&& other) noexcept;

        ~Point2i();

    public:
        int _x;
        int _y;
    };
}; // namespace gut
