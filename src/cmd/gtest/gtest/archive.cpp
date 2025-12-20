#include <map>
#include <set>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(UnitTest, 005)
{
    // 自定义函数
    auto f0 = [](int n) -> bool { return n % 2 == 0; };
    std::function<bool(int)> f1 = [](int n) -> bool { return n % 2 == 0; };
    EXPECT_THAT(4, ::testing::Truly(f0));
    EXPECT_THAT(4, ::testing::Truly(f1));
    EXPECT_THAT(4, ::testing::Truly([](int n) -> bool { return n % 2 == 0; }));

    ::testing::Matcher<int> m0 = ::testing::Gt(3);
    EXPECT_THAT(4, m0);
    EXPECT_THAT(2, ::testing::Not(m0));
}

TEST(UnitTest, 004)
{
    auto m0 = ::testing::SizeIs(1);
    ::testing::Matcher<int> m1 = ::testing::Gt(0);
    auto m2 = ::testing::AllOf(m1, ::testing::Truly([](int n) { return n % 2 == 0; }));

    EXPECT_THAT((std::vector<int>{1, 2, 3, 4, 5}), ::testing::AnyOf(::testing::Contains(0), ::testing::Contains(5)));

    EXPECT_THAT((std::vector<int>{1, 2, 3, 4, 5}),
                ::testing::AllOf(::testing::SizeIs(5), ::testing::Contains(3), ::testing::Each(::testing::Lt(10))));
    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::Each(m1));
    EXPECT_THAT((std::vector<std::string>{"a", "b", "c"}), ::testing::Each(m0));

    EXPECT_THAT((std::vector<int>{2, 4, 6}), ::testing::Each(m2));
    EXPECT_THAT((std::map<std::string, std::vector<int>>{
                    {"even", {2, 4, 6}},
                    {"odd", {1, 3, 5}},
                }),
                ::testing::Contains(::testing::Pair("even", ::testing::Each(m2))));

    std::vector<int> a0{1, 4, 9, 16};
    std::vector<int> e0{1, 2, 3, 4};

    EXPECT_THAT(
        a0, ::testing::Pointwise(
                ::testing::Truly([](const std::tuple<int, int>& pair) { return std::get<0>(pair) == std::get<1>(pair) * std::get<1>(pair); }), e0));

    EXPECT_THAT((std::vector<int>{1, 2, 3, 4, 5}), ::testing::Not(::testing::IsEmpty()));
    EXPECT_THAT((std::vector<int>{1, 2, 3, 4, 5}), ::testing::SizeIs(::testing::Gt(2)));
    EXPECT_THAT((std::vector<int>{1, 2, 3, 4, 5}), ::testing::SizeIs(::testing::Lt(10)));
    EXPECT_THAT((std::vector<int>{1, 2, 3, 4, 5}), ::testing::SizeIs(::testing::AllOf(::testing::Ge(3), ::testing::Le(5))));
    EXPECT_THAT((std::vector<int>{1, 2, 3, 4, 5}), ::testing::Each(::testing::Gt(0)));
    EXPECT_THAT((std::vector<std::string>{"hello", "world", "test"}), ::testing::Each(::testing::SizeIs(::testing::Ge(4))));
    EXPECT_THAT((std::vector<int>{1, 2, 3, 4, 5}), ::testing::Contains(::testing::Gt(4)));
    EXPECT_THAT((std::vector<std::string>{"hello", "world", "test"}), ::testing::Contains(::testing::StartsWith("h")));
    EXPECT_THAT((std::vector<int>{1, 2, 3, 4, 5}), ::testing::Not(::testing::Contains(::testing::Lt(0))));

    EXPECT_THAT((std::vector<int>{1, 2, 3, 4, 5}), ::testing::ElementsAre(::testing::AllOf(::testing::Gt(0), ::testing::Lt(2)), ::testing::_,
                                                                          ::testing::Gt(2), ::testing::Le(4), ::testing::Ge(5)));

    int arr[] = {1, 2, 3};
    EXPECT_THAT(arr, ::testing::ElementsAre(1, 2, 3));
    EXPECT_THAT(std::vector<int>(std::begin(arr), std::end(arr)), ::testing::SizeIs(3));
}

TEST(UnitTest, 003)
{
    // 简单vector
    EXPECT_THAT(std::vector<int>{}, ::testing::IsEmpty());
    EXPECT_THAT(std::vector<int>{}, ::testing::ElementsAre());
    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::SizeIs(3));
    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::Contains(3));
    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::Each(::testing::Gt(0.5)));
    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::SizeIs(::testing::Gt(2)));
    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::SizeIs(::testing::Lt(10)));
    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::Not(::testing::Contains(7)));

    // vector元素等价比较
    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::ElementsAre(1, 2, 3));
    EXPECT_THAT((std::vector<int>{2, 1, 3}), ::testing::Not(::testing::ElementsAre(1, 2, 3)));
    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::UnorderedElementsAre(1, 2, 3));
    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::UnorderedElementsAre(2, 3, 1));
    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::Not(::testing::UnorderedElementsAre(2, 3, 1, 1)));

    EXPECT_THAT((std::vector<int>{1, 2, 3, 4, 5}), ::testing::SizeIs(::testing::AllOf(::testing::Ge(3), ::testing::Le(5))));
    EXPECT_THAT((std::vector<int>{10, 20, 30, 40}), ::testing::Contains(::testing::ResultOf([](int n) { return n % 2 == 0; }, ::testing::Eq(true))));
    EXPECT_THAT((std::vector<int>{10, 20, 30, 40}), ::testing::ElementsAre(::testing::Lt(15), ::testing::Gt(15), ::testing::_, ::testing::Ge(40)));

    EXPECT_THAT((std::vector<int>{2, 1, 3}), ::testing::Not(::testing::AnyOf(::testing::Contains(0), ::testing::Contains(4))));
    EXPECT_THAT((std::vector<int>{4, 5, 6}),
                ::testing::Not(::testing::AnyOf(::testing::Contains(1), ::testing::Contains(2), ::testing::Contains(3))));
    EXPECT_THAT((std::vector<int>{2, 1, 3}), ::testing::Not(::testing::ContainerEq(std::vector<int>{1, 2, 3})));

    EXPECT_THAT((std::vector<int>{4, 5, 6}), ::testing::Not(::testing::UnorderedElementsAre(1, 2, 3)));
    EXPECT_THAT((std::vector<int>{2, 1, 3}), ::testing::Each(::testing::Ne(0)));
    EXPECT_THAT((std::vector<int>{2, 1, 3}), ::testing::Contains(::testing::Ne(1)));
    EXPECT_THAT((std::vector<int>{2, 1, 3}), ::testing::Not(::testing::Contains(0)));
    EXPECT_THAT((std::vector<int>{2, 1, 3}), ::testing::Not(::testing::Contains(4)));

    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::ContainerEq(std::vector<int>{1, 2, 3}));
    EXPECT_EQ((std::vector<int>{1, 2, 3}), (std::vector<int>{1, 2, 3}));
    EXPECT_THAT((std::vector<int>{1, 2, 3}), ::testing::ElementsAreArray(std::vector<int>{1, 2, 3}));
    EXPECT_THAT((std::vector<int>{3, 2, 1}), ::testing::WhenSorted(::testing::ElementsAre(1, 2, 3)));
    EXPECT_THAT((std::vector<int>{3, 1, 4, 2}), ::testing::WhenSortedBy(std::less<int>(), ::testing::ElementsAre(1, 2, 3, 4)));
    EXPECT_THAT((std::vector<int>{2, 1, 3, 5}),
                ::testing::AllOf(::testing::Not(::testing::ElementsAre(1, 2, 3)), ::testing::Contains(::testing::Gt(4))));
    EXPECT_THAT((std::vector<std::string>{"hello", "world", "test"}),
                ::testing::Contains(::testing::ResultOf([](const std::string& s) { return s.length(); }, ::testing::Gt(4))));

    EXPECT_THAT((std::vector<int>{2, 1, 3, 5}), ::testing::AllOf(::testing::Not(::testing::IsEmpty()), ::testing::Each(::testing::Gt(0))));

    EXPECT_THAT(std::vector<std::string>({"hello", "world", "test"}),
                ::testing::ElementsAre(::testing::StartsWith("h"), ::testing::EndsWith("d"), ::testing::StrEq("test")));

    EXPECT_THAT((std::vector<std::string>{"hello", "world", "test"}), ::testing::Each(::testing::SizeIs(::testing::Ge(4))));

    // 简单字符串
    EXPECT_THAT("Hello World 123", ::testing::StartsWith("Hello"));
    EXPECT_THAT("Hello World 123", ::testing::EndsWith("123"));
    EXPECT_THAT("Hello World 123", ::testing::HasSubstr("World"));
    EXPECT_THAT("Hello World 123", ::testing::MatchesRegex("Hello.*123"));
    EXPECT_THAT("Hello World 123", ::testing::StrCaseEq("hello world 123"));
    EXPECT_THAT("Hello World 123", ::testing::Not(::testing::StrCaseEq("goodbye")));

    // 结构体
    struct Person
    {
        std::string name;
        int age;
    };
    EXPECT_THAT((std::vector<Person>{
                    {"Alice", 25},
                    {"Bob", 30},
                }),
                ::testing::Contains(::testing::Field(&Person::name, "Alice")));
    EXPECT_THAT((std::vector<Person>{
                    {"Alice", 25},
                    {"Bob", 30},
                }),
                ::testing::Contains(::testing::Field(&Person::age, ::testing::Gt(20))));

    EXPECT_THAT((std::map<std::string, int>{
                    {"a", 1},
                    {"b", 2},
                    {"c", 3},
                }),
                ::testing::Contains(::testing::Key("a")));
    EXPECT_THAT((std::map<std::string, int>{
                    {"a", 1},
                    {"b", 2},
                    {"c", 3},
                }),
                ::testing::Contains(::testing::Pair(::testing::_, 2)));

    // map
    EXPECT_THAT((std::map<std::string, int>{
                    {"a", 1},
                    {"b", 2},
                    {"c", 3},
                }),
                ::testing::Not(::testing::Contains(::testing::Key("x"))));
    EXPECT_THAT((std::map<std::string, int>{
                    {"a", 1},
                    {"b", 2},
                    {"c", 3},
                }),
                ::testing::Each(::testing::Pair(::testing::SizeIs(1), ::testing::Gt(0))));
    EXPECT_THAT((std::map<std::string, int>{
                    {"a", 1},
                    {"b", 2},
                }),
                ::testing::ElementsAre(::testing::Pair("a", 1), ::testing::Pair("b", 2)));

    // set
    EXPECT_THAT((std::set<int>{1, 2, 3}), ::testing::UnorderedElementsAre(2, 3, 1));
}

TEST(UnitTest, 002)
{
    EXPECT_EQ(std::string("haha"), "haha");
    EXPECT_EQ(int(5), 5);
    EXPECT_FLOAT_EQ(float(5.3), 5.3);
    EXPECT_DOUBLE_EQ(double(5.4), 5.4);

    EXPECT_NE(std::string("haha"), "haha1");
    EXPECT_NE(int(5), 6);
    EXPECT_NE(float(5.3), 5.31);
    EXPECT_NE(double(5.4), 5.41);

    EXPECT_GE(3, 3);
    EXPECT_GE(4, 3);
    EXPECT_GT(4, 3);

    EXPECT_LE(3, 3);
    EXPECT_LE(3, 4);
    EXPECT_LT(3, 4);

    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
    EXPECT_NEAR(3, 2, 1);
    EXPECT_NEAR(2, 3, 1.1);
    EXPECT_THAT((std::vector<double>{1.0, 2.0, 3.0}), ::testing::Each(::testing::DoubleNear(0.0, 3.1)));
    EXPECT_THAT(3.14, ::testing::DoubleEq(3.14));
    EXPECT_THAT(3.14, ::testing::NanSensitiveDoubleEq(3.14));

    EXPECT_THAT((std::vector<int>{1, 2, 3, 4, 5}), ::testing::Contains(::testing::Truly([](int n) { return n % 2 == 0; })));

    int x = 0;
    EXPECT_THAT(&x, ::testing::NotNull());
    EXPECT_THAT(nullptr, ::testing::IsNull());

    EXPECT_NO_THROW((std::array<int, 3>{4, 2, 5}.at(0)));
    EXPECT_ANY_THROW((std::array<int, 3>{4, 2, 5}.at(100)));
    EXPECT_THROW((std::array<int, 3>{4, 2, 5}.at(100)), std::out_of_range);
    EXPECT_DEATH(
        {
            std::cerr << "Fatal error: invalid input" << std::endl;
            exit(1);
        },
        "Fatal error: invalid input");

    int result = [](int x) -> int { return x + 1; }(5);
    EXPECT_EQ(result, 6);
    EXPECT_EQ([](int x) -> int { return x + 1; }(5), 6);

    EXPECT_EXIT(exit(1), ::testing::ExitedWithCode(1), ".*");
    EXPECT_EXIT(abort(), ::testing::KilledBySignal(SIGABRT), ".*");
}

MATCHER_P(UnorderedEquals, expected, "")
{
    auto arg_sorted = arg;
    auto expected_sorted = expected;
    std::sort(arg_sorted.begin(), arg_sorted.end());
    std::sort(expected_sorted.begin(), expected_sorted.end());
    return arg_sorted == expected_sorted;
}

TEST(UnitTest, 001)
{
    EXPECT_THAT((std::vector<int>{2, 1, 3}), UnorderedEquals(std::vector<int>{1, 2, 3}));
}

#endif