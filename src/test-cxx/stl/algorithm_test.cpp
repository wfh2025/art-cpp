#include <algorithm>
#include <functional>
#include <utility>

#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"
#ifdef RUN_ALL_TEST_CASE
TEST(std_minmax, 001)
{
    std::function<bool(int*, int*)> intPtrLess = [](int* a, int* b) -> bool { return (*a < *b); };
    int x = 17;
    int y = 42;
    int z = 33;
    int* px = &x;
    int* py = &y;
    int* pz = &z;
    std::pair<int*, int*> extremes = std::minmax({px, py, pz}, intPtrLess);
    EXPECT_TRUE(extremes.first == px && extremes.second == py);
}

TEST(std_max, 001)
{
    std::function<bool(int*, int*)> intPtrLess = [](int* a, int* b) -> bool { return (*a < *b); };

    int x = 17;
    int y = 42;
    int z = 33;
    int* px = &x;
    int* py = &y;
    int* pz = &z;

    int* pmax = std::max(px, py, intPtrLess);
    EXPECT_EQ(pmax, py);
}

#endif
