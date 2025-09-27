#include "tbb/parallel_for_each.h"
#include "ut_config.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <map>
#include <set>
#include <vector>

#ifdef RUN_ALL_TEST_CASE
TEST(tbb, 001)
{
    std::vector<int> v1 = {2, 3, 4, 5};
    tbb::parallel_for_each(v1.begin(), v1.end(), [](int& x) { x *= 2; });
    EXPECT_THAT(v1, ::testing::ElementsAre(4, 6, 8, 10));
}
#endif