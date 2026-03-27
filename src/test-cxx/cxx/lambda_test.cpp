#include <future>
#include <iostream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(cxx_lambda, 001)
{
    int x = 2;
    int y = 3;
    SPDLOG_INFO("&x: {:p}, &y: {:p}", fmt::ptr(&x), fmt::ptr(&y));
    auto fn0 = [=]() -> int {
        SPDLOG_INFO("&x: {:p}, &y: {:p}", fmt::ptr(&x), fmt::ptr(&y));
        return x + y;
    };
    fn0();

    auto fn1 = [&]() -> int {
        SPDLOG_INFO("&x: {:p}, &y: {:p}", fmt::ptr(&x), fmt::ptr(&y));
        return x + y;
    };
    fn1();

    auto fn2 = [=]() { return x * y; };
    EXPECT_EQ(fn2(), 6);

    auto fn3 = [=] {
        // 1. 参数为空: 省略()
        // 2. 返回类型自动推导,可省略
        return x * y;
    };
    EXPECT_EQ(fn3(), 6);

    // 修改外部值
    int m = 4;
    auto fn4 = [&] { m = 5; };
    fn4();
    EXPECT_EQ(m, 5);

    int x1 = 3;
    int x2 = 4;
    int x3 = 5;
    SPDLOG_INFO("&x1: {:p}, &x2: {:p}, &x3: {:p}", fmt::ptr(&x1), fmt::ptr(&x2), fmt::ptr(&x3));
    auto fn5 = [x1, &x2, x3]() {
        x2 = x1 + x3;
        SPDLOG_INFO("&x1: {:p}, &x2: {:p}, &x3: {:p}", fmt::ptr(&x1), fmt::ptr(&x2), fmt::ptr(&x3));
    };
    fn5();
    EXPECT_EQ((x1 + x3), x2);
}

TEST(cxx_lambda, 002)
{
    auto f1 = []() { return 42; };
    auto f2 = [](int a, int b) { return a + b; };
    auto f3 = [value = 3]() { return value; };

    int x = 10;
    auto multiply = [x](int n) {
        // 两个x地址不同
        return n * x;
    };
    EXPECT_EQ(multiply(3), 30);

    int count = 5;
    auto increment = [&count]() {
        // 两个count地址相同
        count = count + 1;
    };
    increment();
    EXPECT_EQ(count, 6);

    // 自动推导返回值类型是int
    auto square = [](int x) { return x * x; };
    EXPECT_EQ(square(3), 9);

    auto divide = [](int a, int b) -> double { return (b == 0) ? 0.0 : static_cast<double>(a) / b; };

    std::vector<int> v{3, 1, 4, 1, 5};
    std::sort(v.begin(), v.end(), [](int a, int b) { return a < b; });
    EXPECT_THAT(v, ::testing::ElementsAre(1, 1, 3, 4, 5));

    int y = 10;
    auto f4 = [y]() mutable {
        y += 1;
        return y;
    };
    EXPECT_EQ(f4(), 11);
    EXPECT_EQ(y, 10);

    auto factorial = [](int n) {
        auto factImpl = [](int n, const auto& self) -> int { return n <= 1 ? 1 : n * self(n - 1, self); };
        return factImpl(n, factImpl);
    };
    EXPECT_EQ(factorial(4), 24);
    int a = 5, b = 10;
    auto f5 = [&a, &b]() {
        a++;
        b++;
    };
    f5();
    EXPECT_TRUE((a == 6) && (b == 11));
    int a1 = 5, b1 = 6;
    auto f6 = [&]() {
        a1++;
        b1++;
    };
    f6();
    EXPECT_TRUE((a1 == 6) && (b1 == 7));
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 前面: 不满足条件(要保留的数据)；后面: (后面内容不确定，可能是满足条件的数据)
    auto it = std::remove_if(nums.begin(), nums.end(), [](int n) -> bool { return n % 2 == 0; });
    nums.erase(it, nums.end());
    EXPECT_THAT(nums, ::testing::ElementsAre(1, 3, 5, 7, 9));

    auto future = std::async([](int a, int b) { return a * b; }, 6, 7);
    EXPECT_EQ(future.get(), 42);

    std::function<int(const std::string&, const std::string&)> f7 = [](const std::string& s1, const std::string& s2) -> int {
        return s1.size() + s2.size();
    };
    EXPECT_EQ(f7("hello", "wo"), 7);

    int (*f9)(int) = [](int x) { return x * x; };
    EXPECT_EQ(f9(3), 9);

    int y2 = 4;
    std::function<std::string(int)> f10 = [y2](int n) mutable {
        y2++;
        return std::to_string(n);
    };

    EXPECT_TRUE(f10(3) == "3" && y2 == 4);

    auto f11 = []() -> int {
        throw std::runtime_error("lambda error");
        return 42;
    };
    EXPECT_THROW(f11(), std::runtime_error);
}

#endif