#include <functional>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "gut/gtest_def.hpp"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(cxx_ref, 016)
{
    auto fn4 = [](const gut::Point2i&& pt) { SPDLOG_INFO("&pt: {}", fmt::ptr(&pt)); };
    {
        gut::Point2i pt{2, 3};
        fn4(std::move(pt));
        SPDLOG_INFO("{}", std::string(50, '-'));
        fn4(gut::Point2i{4, 5});
        SPDLOG_INFO("{}", std::string(50, '-'));
    }
}

TEST(cxx_ref, 015)
{
    auto fn3 = [](gut::Point2i&& pt) { SPDLOG_INFO("&pt: {}", fmt::ptr(&pt)); };
    {
        gut::Point2i pt{2, 3};
        fn3(std::move(pt));
        SPDLOG_INFO("{}", std::string(50, '-'));
        fn3(gut::Point2i{4, 5});
        SPDLOG_INFO("{}", std::string(50, '-'));
    }
}
TEST(cxx_ref, 014)
{
    auto fn2 = [](const gut::Point2i& pt) { SPDLOG_INFO("&pt: {}", fmt::ptr(&pt)); };
    {
        gut::Point2i pt{2, 3};
        fn2(pt);
        SPDLOG_INFO("{}", std::string(50, '-'));
        fn2(gut::Point2i{4, 5});
        SPDLOG_INFO("{}", std::string(50, '-'));
    }
}
TEST(cxx_ref, 013)
{
    auto fn1 = [](gut::Point2i& pt) { SPDLOG_INFO("&pt: {}", fmt::ptr(&pt)); };
    {
        gut::Point2i pt{5, 6};
        fn1(pt);
    }
}
TEST(cxx_ref, 012)
{
    auto fn0 = [](gut::Point2i pt) { SPDLOG_INFO("&pt: {}", fmt::ptr(&pt)); };
    {
        gut::Point2i pt{2, 3};
        fn0(pt);
        SPDLOG_INFO("{}", std::string(50, '-'));
        fn0(gut::Point2i{4, 5});
        SPDLOG_INFO("{}", std::string(50, '-'));
    }
}

TEST(cxx_ref, 011)
{
    int ulSize = 3;
    std::function<int&()> getSizeRef = [&]() -> int& { return ulSize; };
    std::function<const int&()> getSizeConstRef = [&]() -> const int& { return ulSize; };
    std::function<int()> getSizeValue = [&]() -> int { return ulSize; };
    std::function<int*()> getSizePtr = [&]() -> int* { return &ulSize; };

    EXPECT_EQ(getSizeRef(), getSizeValue());
    EXPECT_TRUE((&getSizeRef() != nullptr) && (&getSizeRef() == &ulSize) && (&getSizeConstRef() == &ulSize) && (&ulSize == getSizePtr()));

    // 如果类型不是引用，即使函数返回引用，也是存在复制
    int v0 = getSizeRef();
    int& v1 = getSizeRef();
    EXPECT_TRUE((&ulSize == &v1) && (&ulSize != &v0));

    // 如果类型不是引用，即使函数返回引用，也是存在复制，auto也是类似
    auto v2 = getSizeRef();  // v2类型: int
    auto& v3 = getSizeRef(); // v3类型: int&
    EXPECT_TRUE((&ulSize == &v3) && (&ulSize != &v2));
    EXPECT_TRUE((std::is_same_v<decltype(v2), int>) && (std::is_same_v<decltype(v3), int&>));

    int v4 = getSizeConstRef();        // 拷贝
    const int v5 = getSizeConstRef();  // 拷贝
    const int& v6 = getSizeConstRef(); // 引用
    EXPECT_TRUE((&v4 != &ulSize) && (&v5 != &ulSize) && (&v6 == &ulSize));

    auto v7 = getSizeConstRef();        // int 拷贝
    auto& v8 = getSizeConstRef();       // const int &, 引用
    const auto& v9 = getSizeConstRef(); // const int &, 引用
    EXPECT_TRUE((&v7 != &ulSize) && (&v8 == &ulSize) && (&v9 == &ulSize));
    EXPECT_TRUE((std::is_same_v<decltype(v7), int>) && (std::is_same_v<decltype(v8), const int&>) && (std::is_same_v<decltype(v9), const int&>));

    int v10 = getSizeValue();
    const int& v11 = getSizeValue();
    EXPECT_TRUE((&v10 != &ulSize) && (&v11 != &ulSize));

    auto v12 = getSizeValue();
    const auto& v13 = getSizeValue();
    EXPECT_TRUE((&v12 != &ulSize) && (&v13 != &ulSize));
    EXPECT_TRUE((std::is_same_v<decltype(v12), int>) && (std::is_same_v<decltype(v13), const int&>));
}

TEST(cxx_ref, 010)
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

TEST(cxx_ref, 009)
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
    EXPECT_TRUE((refHolder.getAddr() == &value) && (value == 11) && (refHolder.getValue() == value));
}

TEST(cxx_ref, 008)
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

TEST(cxx_ref, 007)
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

TEST(cxx_ref, 006)
{
    int a = 1;
    int b = 2;
    std::vector<std::reference_wrapper<int>> refs = {a, b};

    EXPECT_TRUE((&refs[0].get() == &a) && (&refs[1].get() == &b));
    refs[0].get() = 10;
    EXPECT_TRUE((refs[0].get() == a) && (a == 10));
}

TEST(cxx_ref, 005)
{
    std::vector<int> data = {1, 2, 3};
    std::vector<int>& ref = data;
    std::vector<int> moved = std::move(data);
    EXPECT_TRUE(data.empty() && (ref.size() == 0) && (moved.size() == 3));
}

TEST(cxx_ref, 004)
{
    int v0 = 3;
    int v1 = 4;
    int& v2 = v0;
    int&& v3 = 100;
    int&& v4 = v0 + v1;
    EXPECT_TRUE((v0 == 3) && (v1 == 4) && (v2 == 3) && (v4 == 7));
    int&& v5 = std::move(v0); // 基本类型move: 拷贝，原值不变
}

TEST(cxx_ref, 003)
{
    std::function<size_t(const std::string&)> fn0 = [](const std::string& str) -> size_t { return str.length(); };
    std::string str = "hello";
    EXPECT_EQ(fn0(str), 5);
    EXPECT_EQ(fn0("world"), 5);
}

TEST(cxx_ref, 002)
{
    int v0 = 2;
    int v1 = 3;
    int& ref0 = v0;
    ref0 = v1;
    EXPECT_TRUE((&ref0 == &v0) && (&ref0 != &v1));
    EXPECT_TRUE((v0 == 3) && (v1 == 3) && (ref0 == 3));
}

TEST(cxx_ref, 001)
{
    int a = 10;
    int& v0 = a;
    int& v1 = a;
    int& v11 = v1;
    int& v111 = v11;
    v11 = 8;
    EXPECT_TRUE((v111 == v11) && (v11 == a) && (v0 == a) && (v0 == v1) && (a == 8));

    SPDLOG_INFO("&a: {}, &v0: {}, &v1: {}, &v11: {}, &v111: {}", fmt::ptr(&a), fmt::ptr(&v0), fmt::ptr(&v1), fmt::ptr(&v11), fmt::ptr(&v111));

    const int& v3 = 5;
    const int& v4 = a + 3;
    EXPECT_TRUE((&a == &v0) && (&v0 == &v1) && (&v1 == &v11));

    int v5[3] = {1, 2, 3};
    int (&v6)[3] = v5;
    EXPECT_EQ(&v5, &v6);

    v6[1] = 99;
    EXPECT_THAT(v5, ::testing::ElementsAre(1, 99, 3));
    EXPECT_THAT(v6, ::testing::ElementsAre(1, 99, 3));
}
#endif