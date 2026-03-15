#include <future>
#include <ios>
#include <system_error>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "s3/aws_s3.hpp"
#include "spdlog/spdlog.h"
#include "ut_config.h"

TEST(s3_base_OptStr, 002)
{
    using s3::base::OptStr;
    {
        SPDLOG_INFO("{:-^80}", "001");
        OptStr op;
        EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "002");
        OptStr op{};
        EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "003");
        // OptStr op(); // 声明
        // EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "004");
        OptStr op = "abc";
        EXPECT_TRUE((op.has() == true) && (op.value() == "abc"));
        op.reset();
        EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "005");
        OptStr op;
        EXPECT_TRUE(op.has() == false);

        op = "5";
        EXPECT_TRUE((op.has() == true) && (op.value() == "5"));

        op = "3";
        EXPECT_TRUE((op.has() == true) && (op.value() == "3"));
    }
    {
        struct S
        {
            OptStr opt;
        };
        SPDLOG_INFO("{:-^80}", "006");
        S s;
        EXPECT_TRUE(s.opt.has() == false);
    }
    {
        struct S
        {
            OptStr opt = "2";
        };
        SPDLOG_INFO("{:-^80}", "007");
        S s;
        EXPECT_TRUE((s.opt.has() == true) && (s.opt.value() == "2"));
    }
    {
        struct S
        {
            OptStr opt{"2"};
        };
        SPDLOG_INFO("{:-^80}", "008");
        S s;
        EXPECT_TRUE((s.opt.has() == true) && (s.opt.value() == "2"));
    }

    int32_t x;
    int64_t y;
}

#ifdef RUN_ALL_TEST_CASE
TEST(s3_base_OptI64, 001)
{
    using s3::base::OptI64;
    {
        SPDLOG_INFO("{:-^80}", "001");
        OptI64 op;
        EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "002");
        OptI64 op{};
        EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "003");
        // 函数声明
        // OptI64 op();
    }
    {
        SPDLOG_INFO("{:-^80}", "004");
        OptI64 op = 4;
        EXPECT_TRUE((op.has() == true) && (op.value() == 4));
        op.reset();
        EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "005");
        OptI64 op;
        EXPECT_TRUE(op.has() == false);

        op = 5;
        EXPECT_TRUE((op.has() == true) && (op.value() == 5));

        op = 3;
        EXPECT_TRUE((op.has() == true) && (op.value() == 3));
    }
    {
        struct S
        {
            OptI64 opt;
        };
        SPDLOG_INFO("{:-^80}", "006");
        S s;
        EXPECT_TRUE(s.opt.has() == false);
    }
    {
        struct S
        {
            OptI64 opt = 2;
        };
        SPDLOG_INFO("{:-^80}", "007");
        S s;
        EXPECT_TRUE((s.opt.has() == true) && (s.opt.value() == 2));
    }
    {
        struct S
        {
            OptI64 opt{2};
        };
        SPDLOG_INFO("{:-^80}", "008");
        S s;
        EXPECT_TRUE((s.opt.has() == true) && (s.opt.value() == 2));
    }
}

TEST(timeToISO8601, 001)
{
    std::string str = "";
    std::chrono::system_clock::time_point tp0 = std::chrono::system_clock::now();
    str = s3::timeToISO8601(tp0);

    std::chrono::system_clock::time_point tp1(std::chrono::milliseconds(1698706800123));
    str = s3::timeToISO8601(tp1);
    std::cout << str << std::endl;
}
#endif