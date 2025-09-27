#include "ut_config.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

static char* fnVal(std::string str)
{
    return str.data();
}
static char* fnLeftRef(std::string& str)
{
    return str.data();
}
static const char* fnConstLeftRef(const std::string& str)
{
    return str.data();
}
static char* fnRightRef(std::string&& str)
{
    return str.data();
}
static const char* fnConstRightRef(const std::string&& str)
{
    return str.data();
}

#ifdef RUN_ALL_TEST_CASE
TEST(Ref, 001)
{
    int a = 10;
    int& v0 = a;
    int& v1 = a;
    int& v11 = v1;

    const int& v3 = 5;
    const int& v4 = a + 3;
    EXPECT_TRUE((v11 == a) && (v0 == a) && (v0 == v1));
    EXPECT_TRUE((&a == &v0) && (&v0 == &v1) && (&v1 == &v11));

    int v5[3] = {1, 2, 3};
    int (&v6)[3] = v5;
    EXPECT_EQ(&v5, &v6);

    v6[1] = 99;
    EXPECT_THAT(v5, ::testing::ElementsAre(1, 99, 3));
    EXPECT_THAT(v6, ::testing::ElementsAre(1, 99, 3));
}

TEST(Ref, 002)
{
    int v0 = 2;
    int v1 = 3;
    int& ref0 = v0;
    ref0 = v1;

    EXPECT_TRUE((&ref0 == &v0) && (&ref0 != &v1));
    EXPECT_TRUE((v0 == v1) && (v0 == 3) && (ref0 == v1));
}
static int g_ulSize = 3;
static int& getSizeRef()
{
    return g_ulSize;
}

static const int& getSizeConstRef()
{
    return g_ulSize;
}
static int getSizeValue()
{
    return g_ulSize;
}
static int* getSizePtr()
{
    return &g_ulSize;
}

TEST(Ref, 003)
{
    EXPECT_EQ(getSizeRef(), getSizeValue());
    EXPECT_TRUE((&getSizeRef() != nullptr) && (&getSizeRef() == &g_ulSize) &&
                (&getSizeConstRef() == &g_ulSize) && (&g_ulSize == getSizePtr()));

    int v0 = getSizeRef();
    int& v1 = getSizeRef();
    auto v2 = getSizeRef();
    auto& v3 = getSizeRef();
    EXPECT_TRUE((&g_ulSize == &getSizeRef()) && (g_ulSize == v0) && (g_ulSize == v1) &&
                (g_ulSize == v2) && (g_ulSize == v3) && (&v0 != &g_ulSize) && (&v1 == &g_ulSize) &&
                (&v2 != &g_ulSize) && (&v3 == &g_ulSize));
    EXPECT_TRUE((true == std::is_same_v<decltype(getSizeRef()), int&>) &&
                (true == std::is_same_v<decltype(v0), int>) &&
                (true == std::is_same_v<decltype(v1), int&>) &&
                (true == std::is_same_v<decltype(v2), int>) &&
                (true == std::is_same_v<decltype(v3), int&>));

    int v4 = getSizeConstRef();
    auto v5 = getSizeConstRef();
    auto& v6 = getSizeConstRef();
    const auto& v7 = getSizeConstRef();
    EXPECT_TRUE((&g_ulSize == &getSizeConstRef()) && (g_ulSize == v4) && (g_ulSize == v5) &&
                (g_ulSize == v6) && (g_ulSize == v7) && (&g_ulSize != &v4) && (&g_ulSize != &v5) &&
                (&g_ulSize == &v6) && (&g_ulSize == &v7));
    EXPECT_TRUE((true == std::is_same_v<decltype(getSizeConstRef()), const int&>) &&
                (true == std::is_same_v<decltype(v4), int>) &&
                (true == std::is_same_v<decltype(v5), int>) &&
                (true == std::is_same_v<decltype(v6), const int&>) &&
                (true == std::is_same_v<decltype(v7), const int&>));
}

TEST(Ref, 004)
{
    std::vector<int> v0 = {1, 2, 3};
    for (int ele : v0)
    {
        ele *= 2;
    }
    EXPECT_THAT(v0, ::testing::ElementsAre(1, 2, 3));
    for (int& ele : v0)
    {
        ele *= 2;
    }
    EXPECT_THAT(v0, ::testing::ElementsAre(2, 4, 6));
}

TEST(Ref, 005)
{
    int* p = nullptr;
    {
        int local = 3;
        int& r = local;
        p = &r;
        EXPECT_EQ(*p, local);
    }
    // p失效
}

TEST(Ref, 006)
{
    std::function<size_t(const std::string&)> fn0 = [](const std::string& str) -> size_t {
        return str.length();
    };
    std::string str = "hello";
    EXPECT_EQ(fn0(str), 5);
    EXPECT_EQ(fn0("world"), 5);
}

TEST(Ref, 007)
{
    class RefHolder
    {
    private:
        int& ref_;

    public:
        RefHolder(int& value) : ref_(value) {}
        void incr()
        {
            ++ref_;
        }
        int getValue() const
        {
            return ref_;
        }
        int* getAddr() const
        {
            return &ref_;
        }
    };

    int value = 10;
    RefHolder refHolder(value);
    refHolder.incr();
    EXPECT_TRUE((refHolder.getAddr() == &value) && (value == 11) &&
                (refHolder.getValue() == value));
}

TEST(Ref, 008)
{
    class Base
    {
    public:
        virtual std::string name()
        {
            return "Base";
        }
    };
    class Derived : public Base
    {
    public:
        std::string name() override
        {
            return "Derived";
        }
    };

    Derived d;
    Base& ref = d;
    EXPECT_EQ(ref.name(), "Derived");
}

TEST(Ref, 009)
{
    int a = 1;
    int b = 2;
    std::vector<std::reference_wrapper<int>> refs = {a, b};

    EXPECT_TRUE((&refs[0].get() == &a) && (&refs[1].get() == &b));
    refs[0].get() = 10;
    EXPECT_TRUE((refs[0].get() == a) && (a == 10));
}

TEST(Ref, 010)
{
    std::vector<int> data = {1, 2, 3};
    std::vector<int>& ref = data;
    std::vector<int> moved = std::move(data);

    EXPECT_TRUE(data.empty() && (ref.size() == 0) && (moved.size() == 3));
}

TEST(Ref, 011)
{
    int v0 = 3;
    int v1 = 4;
    int& v2 = v0;
    int&& v3 = 100;
    int&& v4 = v0 + v1;
    EXPECT_TRUE((v0 == 3) && (v1 == 4) && (v2 == 3) && (v4 == 7));
    int&& v5 = std::move(v0); // 基本类型move: 拷贝，原值不变
}

TEST(Ref, 012)
{
    // vector类型move: 原来值为空，不可使用原来值
    std::vector<int> v0 = {1, 2, 3};
    std::vector<int> v1 = std::move(v0);
    EXPECT_THAT(v1, ::testing::ElementsAre(1, 2, 3));
    EXPECT_TRUE(v0.size() == 0);

    // unique_ptr类型move: 原来值为空，不可使用原来值
    std::unique_ptr<int> v2 = std::make_unique<int>(42);
    std::unique_ptr<int> v3 = std::move(v2);
    EXPECT_TRUE((v2 == nullptr) && (*v3 == 42));

    // shared_ptr类型move: 原来值为空，不可使用原来值
    std::shared_ptr<int> v4 = std::make_shared<int>(3);
    std::shared_ptr<int> v5 = std::move(v4);
    EXPECT_TRUE((v4.use_count() == 0) && (v4 == nullptr));
    EXPECT_TRUE((v5.use_count() == 1) && (v5 != nullptr));
}

#endif