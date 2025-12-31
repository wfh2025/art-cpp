#include <functional>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(std_ref, 002)
{
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<std::reference_wrapper<int>> refs;
    for (int& num : nums)
    {
        refs.push_back(std::ref(num));
    }

    for (auto ref : refs)
    {
        ref.get() = ref.get() * 2;
    }
    EXPECT_THAT(nums, ::testing::ElementsAre(2, 4, 6, 8, 10));
}

TEST(std_ref, 001)
{
    auto increment = [](int& n) { n++; };

    {
        int x = 0;
        auto fn = std::bind(increment, std::ref(x));
        fn();
        EXPECT_EQ(x, 1);
    }

    {
        int x = 0;
        auto fn = std::bind(increment, x);
        fn();
        EXPECT_EQ(x, 0);
    }
}

#endif