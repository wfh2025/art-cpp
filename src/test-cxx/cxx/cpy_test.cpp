#include <iostream>
#include <random>

#include "gtest/gtest.h"
#include "gut/gtest_def.hpp"
#include "spdlog/spdlog.h"
#ifdef RUN_ALL_TEST_CASE
TEST(cxx_cpy, 001)
{
    using gut::X;
    {
        SPDLOG_INFO("{:-^80}", "001");
        X x; // X()
    }
    {
        SPDLOG_INFO("{:-^80}", "002");
        X x{};
    }
    {
        SPDLOG_INFO("{:-^80}", "003");
        // X x(); // ==> 函数声明, 未构造对象
    }
    {
        SPDLOG_INFO("{:-^80}", "004");
        X x(2); // X(int v)
    }
    {
        SPDLOG_INFO("{:-^80}", "005");
        X x = {};
    }
    {
        SPDLOG_INFO("{:-^80}", "006");
        X x = X{};
    }
    {
        SPDLOG_INFO("{:-^80}", "007");
        X x = X();
    }
    {
        SPDLOG_INFO("{:-^80}", "008");
        X x = X{3};
    }
    {
        SPDLOG_INFO("{:-^80}", "009");
        X x = X(3);
    }
    {
        SPDLOG_INFO("{:-^80}", "010");
        X x{3};
        auto fn = [](X x) {
            // 存在拷贝: X(const X& other)
        };
        fn(x);
    }
    {
        SPDLOG_INFO("{:-^80}", "011");
        X x{3};
        auto fn = [](X x) {};
        X x1 = std::move(x);
    }

    {
        SPDLOG_INFO("{:-^80}", "012");
        X x{3};
        auto fn = [](X x) {};
        fn(std::move(x));
    }
}
#endif