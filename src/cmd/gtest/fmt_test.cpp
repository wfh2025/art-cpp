#include "fmt/core.h"
#include "ut_config.h"
#include "gtest/gtest.h"

#ifdef RUN_ALL_TEST_CASE
TEST(format, 001)
{
    std::string output = fmt::format("{}, {:.2f}", "str", 3.14159);
    EXPECT_EQ(output, "str, 3.14");
}
#endif