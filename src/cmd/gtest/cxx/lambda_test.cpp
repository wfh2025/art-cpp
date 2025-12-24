#include <iostream>
#include <random>

#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(TestCaseLambda, 001)
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

#endif