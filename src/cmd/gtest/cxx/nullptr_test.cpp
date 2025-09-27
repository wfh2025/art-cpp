#include "ut_config.h"
#include "utils.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

static int fn0(int n)
{
    return 1;
}
static int fn0(void* p)
{
    return 2;
}

#ifdef RUN_ALL_TEST_CASE
TEST(nullptr, 001)
{
    EXPECT_EQ(fn0(0), 1);
    EXPECT_EQ(fn0(nullptr), 2);
    // 错误: fn0(NULL);
}

#endif