#include <string>

#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"

TEST(std_string, 001)
{
    std::string s1;
    EXPECT_TRUE(s1.empty());

    std::string s2 = "Hello";
    EXPECT_EQ(s2, "Hello");
    EXPECT_NE(s2, "World");

    std::string s3(5, 'A');
    EXPECT_EQ(s3, "AAAAA");

    std::string s4 = "Hello World";
    EXPECT_EQ(s4.length(), 11);
    EXPECT_EQ(s4.size(), 11);
    EXPECT_FALSE(s4.empty());
    EXPECT_EQ(s4[0], 'H');
    EXPECT_EQ(s4.at(0), 'H');
    EXPECT_EQ(s4.front(), 'H');
    EXPECT_EQ(s4.back(), 'd');
    EXPECT_THROW(s4.at(100), std::out_of_range);

    std::string s5 = "Hello";
    s5.append(" World");
    EXPECT_EQ(s5, "Hello World");
}

#ifdef RUN_ALL_TEST_CASE

#endif