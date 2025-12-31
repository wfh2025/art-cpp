#include <complex>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(std_tuple, 001)
{
    std::tuple<std::string, int, int, std::complex<double>> t0;
    EXPECT_DOUBLE_EQ(std::get<3>(t0).real(), 0);
    EXPECT_DOUBLE_EQ(std::get<3>(t0).imag(), 0);
    EXPECT_TRUE((std::get<0>(t0) == "") && (std::get<1>(t0) == 0) && (std::get<2>(t0) == 0));

    std::tuple<std::string, int, std::complex<double>> t1("haha", 2, std::complex<double>(4.0, 3.0));
    EXPECT_DOUBLE_EQ(std::get<2>(t1).real(), 4.0);
    EXPECT_DOUBLE_EQ(std::get<2>(t1).imag(), 3.0);
    EXPECT_TRUE((std::get<0>(t1) == "haha") && (std::get<1>(t1) == 2));

    auto t2 = std::make_tuple(std::string("haha"), 2, std::complex<double>(4.0, 3.0));
    EXPECT_DOUBLE_EQ(std::get<2>(t2).real(), 4.0);
    EXPECT_DOUBLE_EQ(std::get<2>(t2).imag(), 3.0);
    EXPECT_TRUE((std::get<0>(t2) == "haha") && (std::get<1>(t2) == 2));
}

TEST(std_pair, 001)
{
    std::pair<std::string, int> p0;
    EXPECT_EQ(p0.first, "");
    EXPECT_EQ(p0.second, 0);

    std::pair<std::string, int> p1("ABC", 3);
    EXPECT_EQ(p1.first, "ABC");
    EXPECT_EQ(p1.second, 3);

    std::pair<std::string, int> p2 = p1;
    EXPECT_EQ(p2.first, "ABC");
    EXPECT_EQ(p2.second, 3);

    std::pair<std::string, int> p5("ABC", 3);
    std::pair<std::string, int> p6(std::move(p5));
    EXPECT_EQ(p6.first, "ABC");
    EXPECT_EQ(p6.second, 3);

    auto p7 = std::make_pair("EFG", 4);
    EXPECT_EQ(p7.first, "EFG");
    EXPECT_EQ(p7.second, 4);
}

#endif