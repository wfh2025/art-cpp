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
    EXPECT_EQ(s4[0], 'H');    // 不检查越界
    EXPECT_EQ(s4.at(0), 'H'); // 检查越界,越界抛出异常
    EXPECT_EQ(s4.front(), 'H');
    EXPECT_EQ(s4.back(), 'd');
    EXPECT_THROW(s4.at(100), std::out_of_range);

    std::string s5 = "Hello";
    s5.append(" World");
    EXPECT_EQ(s5, "Hello World");

    std::string s6("World");
    std::string s7(s6);

    std::string s8 = s5 + "-" + s6;
    EXPECT_EQ(s8, "Hello World-World");

    s6 = "gaga";
    EXPECT_EQ(s7, "World");

    std::string s9 = "sorry";
    EXPECT_GT(s9.capacity(), s9.size());
    size_t oldCapacity = s9.capacity();
    s9.shrink_to_fit();
    size_t newCapactiy = s9.capacity();
    EXPECT_GE(newCapactiy, s9.size());
    EXPECT_LE(newCapactiy, oldCapacity);

    s9.reserve(99);
    EXPECT_GE(s9.capacity(), 99);

    std::string s10 = "x";
    s10.push_back('!');
    EXPECT_EQ(s10, "x!");

    std::string s11 = "0123456789";
    s11.insert(5, "ABCD");
    EXPECT_EQ(s11, "01234ABCD56789");

    std::string s12 = "0123456789";
    s12.erase(5, 3);
    EXPECT_EQ(s12, "0123489");

    std::string s13 = "0123456789";
    s13.replace(3, 4, "ABCDEFG"); // replace(size_t pos, size_t count, const string& str);
    EXPECT_EQ(s13, "012ABCDEFG789");
    s13.clear();
    EXPECT_EQ(s13, "");

    std::string s14 = "ABCD";
    std::string::size_type pos0 = s14.find("CD");
    EXPECT_EQ(pos0, 2);

    std::string::size_type pos1 = s14.find('B');
    EXPECT_EQ(pos1, 1);

    std::string::size_type pos2 = s14.find("X");
    EXPECT_EQ(pos2, std::string::npos);

    std::string s15 = "AB|BA|D";
    std::string::size_type pos3 = s15.rfind("B");
    EXPECT_EQ(pos3, 3);

    std::string s16 = "Hello World";
    EXPECT_EQ(s16.find_first_of("oWd"), 4);
    EXPECT_EQ(s16.find_first_of("Wd"), 6);
    EXPECT_EQ(s16.find_first_of("d"), 10);
    EXPECT_EQ(s16.find_first_of("X"), std::string::npos);
    EXPECT_EQ(s16.find_last_of("oWd"), 10);

    std::string s17 = "0134AbCD456";
    EXPECT_EQ(s17.find_first_not_of("012345678"), 4);
    EXPECT_EQ(s17.find_first_not_of("0134AbCD456"), std::string::npos);
    EXPECT_EQ(s17.find_last_not_of("012345678"), 7);

    std::string s18 = "01234567";
    EXPECT_EQ(s18.substr(4, 2), "45");
    EXPECT_EQ(s18.substr(6), "67");

    EXPECT_EQ(std::to_string(123), "123");

    std::string s19(std::move(std::string("Move")));
    EXPECT_EQ(s19, "Move");

    const char* arr = "Array";
    std::string s20(arr, arr + 5);
    EXPECT_EQ(s20, "Array");
}

#ifdef RUN_ALL_TEST_CASE

#endif