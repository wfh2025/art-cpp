#include <memory>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "gut/gtest_def.hpp"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(std_shared_ptr, 001)
{
    {
        // 空判断:
        // <1> ptr == nullptr
        // <2> if (!ptr) {}
        std::shared_ptr<int> ptr;
        EXPECT_TRUE((ptr == nullptr) && (!ptr == true));

        // 非空判断:
        // <1> ptr != nullptr
        // <2> if (ptr) {}
        std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
        EXPECT_TRUE((ptr1 != nullptr) && (ptr1.use_count() == 1) && (*ptr1 == 10));

        std::shared_ptr<int> ptr2 = std::make_shared<int>(20);
        EXPECT_TRUE((ptr2 != nullptr) && (ptr2.use_count() == 1) && (*ptr2 == 20));

        // 赋值拷贝
        std::shared_ptr<int> ptr3 = ptr1;
        EXPECT_TRUE((ptr1 != nullptr) && (ptr1.use_count() == 2) && (*ptr1 == 10));
        EXPECT_TRUE((ptr3 != nullptr) && (ptr3.use_count() == 2) && (*ptr3 == 10));
        EXPECT_TRUE(ptr1.get() == ptr3.get());

        // 尽量不要使用get()方法比较裸指针, 违背封装原则
        EXPECT_TRUE((ptr1 == ptr3) && (ptr1.get() == ptr3.get())); // 二者等价,比较裸地址相等
        EXPECT_TRUE((ptr1 != ptr2) && (ptr1.get() != ptr2.get())); // 二者等价,比较裸地址不等
        EXPECT_TRUE((ptr1 == ptr2) == false);                      // 使用'=='比较
        EXPECT_TRUE((ptr1 != ptr3) == false);                      // 使用'!='比较
        EXPECT_TRUE((ptr1 < ptr2) || (ptr1 > ptr2));               // 无业务意义,仅用在std::set/std::map等容器
    }
    {
        auto fn = [](std::shared_ptr<int> p) { EXPECT_TRUE(p.use_count() == 2); };
        std::shared_ptr<int> ptr = std::make_shared<int>(3);
        fn(ptr);
    }
    {
        auto fn = [](std::shared_ptr<int>& p) { EXPECT_TRUE(p.use_count() == 1); };
        std::shared_ptr<int> ptr = std::make_shared<int>(3);
        fn(ptr);
    }
    {
        // 智能指针对象地址/堆对象指针相关形式值比较
        std::shared_ptr<gut::Point2i> ptr = std::make_shared<gut::Point2i>(30, 40);
        std::shared_ptr<gut::Point2i>* p0 = &ptr; // 智能指针对象地址
        gut::Point2i* p1 = ptr.get();             // 裸指针
        gut::Point2i* p2 = &(*ptr);               // 裸指针
        EXPECT_TRUE((static_cast<void*>(p0) != static_cast<void*>(p1)) && (p1 == p2));
    }
    {
        std::shared_ptr<int> ptr = std::make_shared<int>(100);
        EXPECT_TRUE((ptr != nullptr) && (ptr.get() != nullptr) && (ptr.use_count() == 1) && (*ptr == 100));

        ptr.reset();
        EXPECT_TRUE((ptr == nullptr) && (ptr.get() == nullptr) && (ptr.use_count() == 0));

        ptr.reset(new int(8));
        EXPECT_TRUE((ptr != nullptr) && (ptr.get() != nullptr) && (ptr.use_count() == 1) && (*ptr == 8));

        ptr.reset(new int(3), std::default_delete<int>());
        EXPECT_TRUE((ptr != nullptr) && (ptr.get() != nullptr) && (ptr.use_count() == 1) && (*ptr == 3));
    }
    {
        std::shared_ptr<int> ptr = std::make_shared<int>(5);
        EXPECT_TRUE((ptr != nullptr) && (*ptr == 5) && (ptr.use_count() == 1));

        // std::move后为空
        int* rawPtr = ptr.get();
        std::shared_ptr<int> ptr2 = std::move(ptr);
        EXPECT_TRUE((ptr2 != nullptr) && (ptr2.get() == rawPtr) && (ptr2.use_count() == 1));
        EXPECT_TRUE((ptr == nullptr) && (ptr.get() == nullptr) && (ptr.use_count() == 0));
        rawPtr = nullptr;
    }
    {
        // 简单自定义释放内存
        int* rawPtr = new int(100);
        std::shared_ptr<int> ptr(rawPtr, [](int* p) { delete p; });
        rawPtr = nullptr;
    }
    {
        struct Data
        {
            int _x;
            int _y;
            Data(int x, int y) : _x(x), _y(y) {}
        };

        std::shared_ptr<Data> ptr = std::make_shared<Data>(10, 20);
        EXPECT_TRUE((ptr.use_count() == 1) && (ptr->_x == 10) && (ptr->_y == 20));

        std::shared_ptr<int> alias(ptr, &ptr->_x);
        EXPECT_TRUE((alias.use_count() == 2) && (*alias == 10));
        EXPECT_TRUE((ptr.use_count() == 2) && (ptr->_x == 10) && (ptr->_y == 20));

        ptr->_x = 100;
        EXPECT_TRUE((alias.use_count() == 2) && (*alias == 100));
        EXPECT_TRUE((ptr.use_count() == 2) && (ptr->_x == 100) && (ptr->_y == 20));
    }
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
        EXPECT_TRUE(ptr->value() == 2);

        std::shared_ptr<Derived> derived = std::dynamic_pointer_cast<Derived>(ptr);
        EXPECT_TRUE((derived != nullptr) && (derived->value() == 2));

        std::shared_ptr<Base> base = std::static_pointer_cast<Base>(derived);
        EXPECT_TRUE((base != nullptr) && (base->value() == 2));
    }
}

TEST(std_shared_ptr, 002)
{
    {
        // required: CXX >= C++17
        int* arr = new int[3];
        std::shared_ptr<int[]> ptr(arr);
        arr = nullptr;
    }
    {
        // required: CXX >= C++17
        int* arr = new int[3]{8, 9, 10};
        std::shared_ptr<int[]> ptr(arr);
        arr = nullptr;
    }
    {
        // required: CXX >= C++17
        std::shared_ptr<int[]> ptr;
        ptr.reset(new int[3]);
    }
    {
        // required: CXX >= C++17
        std::shared_ptr<int[]> ptr;
        ptr.reset(new int[3]{9, 10, 11});
    }
    {
        int* arr = new int[3];
        std::shared_ptr<int> ptr(arr, std::default_delete<int[]>());
        arr = nullptr;
    }
    {
        int* arr = new int[3]{6, 7, 8};
        std::shared_ptr<int> ptr(arr, std::default_delete<int[]>());
        arr = nullptr;
    }
    {
        int* arr = new int[3]{6, 7, 8};
        std::shared_ptr<int> ptr(arr, [](int* p) { delete[] p; });
        arr = nullptr;
    }
    {
        std::shared_ptr<int> ptr;
        ptr.reset(new int[3], [](int* p) { delete[] p; });
    }
    {
        std::shared_ptr<int> ptr;
        ptr.reset(new int[3]{6, 7, 8}, [](int* p) { delete[] p; });
    }

    {
        std::shared_ptr<int> ptr;
        ptr.reset(new int[3], std::default_delete<int[]>());
    }
    {
        std::shared_ptr<int> ptr;
        ptr.reset(new int[3]{6, 7, 8}, std::default_delete<int[]>());
    }

    {
        int* rawPtr = new int(100);
        std::shared_ptr<int> ptr(rawPtr, [](int* p) { delete p; });
        rawPtr = nullptr;
    }
    {
        int* rawPtr = new int;
        std::shared_ptr<int> ptr(rawPtr, std::default_delete<int>());
        rawPtr = nullptr;
    }
    {
        std::shared_ptr<int> ptr;
        ptr.reset(new int(100), [](int* p) { delete p; });
    }
    {
        std::shared_ptr<int> ptr;
        ptr.reset(new int(100), std::default_delete<int>());
    }
    {
        std::shared_ptr<int> ptr;
        ptr.reset(new int, [](int* p) { delete p; });
    }
    {
        std::shared_ptr<int> ptr;
        ptr.reset(new int, std::default_delete<int>());
    }
}

TEST(std_shared_ptr, 003)
{
    std::shared_ptr<int> gPtr = std::make_shared<int>(100);

    auto fn0 = [&]() -> std::shared_ptr<int> { return gPtr; };
    auto fn1 = [&]() -> std::shared_ptr<int>& { return gPtr; };

    EXPECT_TRUE((gPtr != nullptr) && (gPtr.use_count() == 1));
    auto tmpPtr0 = fn0();
    EXPECT_TRUE((tmpPtr0 != nullptr) && (tmpPtr0.use_count() == 2));
    EXPECT_TRUE((gPtr != nullptr) && (gPtr.use_count() == 2));

    std::shared_ptr<int>& tmpPtr1 = fn1();
    EXPECT_TRUE((tmpPtr1 != nullptr) && (tmpPtr1.use_count() == 2));
}
#endif