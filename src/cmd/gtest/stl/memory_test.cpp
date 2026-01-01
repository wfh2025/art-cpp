#include <memory>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(std_shared_ptr, 009)
{
    struct Data
    {
        int x;
        int y;
    };

    auto ptr = std::make_shared<Data>(Data{10, 20});

    std::shared_ptr<int> alias(ptr, &ptr->x);

    EXPECT_EQ(ptr.use_count(), 2);
    EXPECT_EQ(alias.use_count(), 2);
    EXPECT_EQ(*alias, 10);

    ptr->x = 100;
    EXPECT_EQ(*alias, 100);
}

TEST(std_shared_ptr, 008)
{
    struct Node
    {
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;
        int value;

        Node(int val) : value(val) {}
    };
    auto node1 = std::make_shared<Node>(1);
    auto node2 = std::make_shared<Node>(2);

    node1->next = node2;
    node2->prev = node1;

    EXPECT_EQ(node1.use_count(), 1);
    EXPECT_EQ(node2.use_count(), 2);

    auto prev = node2->prev.lock();
    EXPECT_NE(prev, nullptr);
    EXPECT_EQ(prev->value, 1);
}

TEST(std_shared_ptr, 007)
{
    struct Resource
    {
        Resource(bool& constructed, bool& destroyed) : constructed(constructed), destroyed(destroyed)
        {
            constructed = true;
        }
        ~Resource()
        {
            destroyed = true;
        }
        bool& constructed;
        bool& destroyed;
    };

    bool constructed = false;
    bool destroyed = false;

    try
    {
        auto ptr = std::make_shared<Resource>(constructed, destroyed);
        EXPECT_TRUE(constructed);
        throw std::runtime_error("test exception");
    }
    catch (...)
    {
        EXPECT_TRUE(destroyed);
    }
}

TEST(std_shared_ptr, 006)
{
    class Base
    {
    public:
        virtual ~Base() = default;
        virtual int value() const
        {
            return 1;
        }
    };

    class Derived : public Base
    {
    public:
        int value() const override
        {
            return 2;
        }
    };
    std::shared_ptr<Base> ptr = std::make_shared<Derived>();
    EXPECT_EQ(ptr->value(), 2);

    std::shared_ptr<Derived> derived = std::dynamic_pointer_cast<Derived>(ptr);
    EXPECT_NE(derived, nullptr);
    EXPECT_EQ(derived->value(), 2);

    std::shared_ptr<Base> base = std::static_pointer_cast<Base>(derived);
    EXPECT_NE(base, nullptr);
}

TEST(std_shared_ptr, 005)
{
    auto ptr1 = std::make_shared<int>(10);
    auto ptr2 = std::make_shared<int>(20);
    auto ptr3 = ptr1;

    EXPECT_TRUE(ptr1 == ptr3);
    EXPECT_FALSE(ptr1 == ptr2);
    EXPECT_TRUE(ptr1 != ptr2);
    EXPECT_FALSE(ptr1 != ptr3);

    EXPECT_TRUE(ptr1 < ptr2 || ptr2 < ptr1);
}

TEST(std_shared_ptr, 004)
{
    auto ptr = std::make_shared<double>(3.14);

    ptr.reset();
    EXPECT_EQ(ptr, nullptr);
    EXPECT_EQ(ptr.use_count(), 0);

    ptr.reset(new double(2.71));
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 2.71);
    EXPECT_EQ(ptr.use_count(), 1);

    ptr.reset(new double(1.41), std::default_delete<double>());
    EXPECT_EQ(*ptr, 1.41);
}

TEST(std_shared_ptr, 003)
{
    {
        auto deleter = [](int* p) {
            SPDLOG_INFO("Succeed to exec delete, ptr: {}", fmt::ptr(p));
            delete p;
        };
        int* rawPtr = new int(100);
        SPDLOG_INFO("Succeed to exec new, ptr: {}", fmt::ptr(rawPtr));
        std::shared_ptr<int> ptr(rawPtr, deleter);
        rawPtr = nullptr;
        SPDLOG_INFO("Succeed to shared_ptr get(), ptr: {}", fmt::ptr(ptr.get()));
    }
}

TEST(std_shared_ptr, 002)
{
    std::shared_ptr<std::vector<int>> ptr1 = std::make_shared<std::vector<int>>(std::initializer_list<int>{1, 2});
    std::vector<int>* rawPtr = ptr1.get();
    std::vector<int>::size_type rawSize = rawPtr->size();
    std::shared_ptr<std::vector<int>> ptr2 = std::move(ptr1);

    EXPECT_EQ(ptr1, nullptr);
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(ptr2.get(), rawPtr);
    EXPECT_EQ(ptr2->size(), rawSize);
}

TEST(std_shared_ptr, 001)
{
    {
        std::shared_ptr<int> ptr = std::make_shared<int>(42);
        EXPECT_NE(ptr, nullptr);
        EXPECT_EQ(*ptr, 42);
        EXPECT_EQ(ptr.use_count(), 1);
    }
    {
        std::shared_ptr<std::string> ptr1 = std::make_shared<std::string>("Hello");
        std::shared_ptr<std::string> ptr2 = ptr1;
        EXPECT_EQ(*ptr1, *ptr2);
        EXPECT_NE(&ptr1, &ptr2);
        EXPECT_TRUE((ptr1.use_count() == 2) && (ptr2.use_count() == 2));
        {
            std::shared_ptr<std::string> ptr3 = ptr2;
            EXPECT_TRUE((ptr1.use_count() == 3) && (ptr2.use_count() == 3) && (ptr3.use_count() == 3));
        }
        EXPECT_TRUE((ptr1.use_count() == 2) && (ptr2.use_count() == 2));
    }
}
#endif