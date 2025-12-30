#include <utility>

#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
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