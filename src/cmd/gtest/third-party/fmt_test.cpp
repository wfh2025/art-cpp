#include "fmt/core.h"
#include "gtest/gtest.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(format, 001)
{
    std::string output = fmt::format("{}, {:.2f}", "str", 3.14159);
    EXPECT_EQ(output, "str, 3.14");
}
#endif