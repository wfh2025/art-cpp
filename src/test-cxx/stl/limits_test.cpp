#include <limits>

#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(std_numeric_limits, 001)
{
    EXPECT_TRUE((std::numeric_limits<short>::max() == 32767) && (std::numeric_limits<short>::min() == -32768));

    EXPECT_FLOAT_EQ(1.1754944e-38, std::numeric_limits<float>::min());
    EXPECT_FLOAT_EQ(3.4028235e+38, std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(-3.4028235e+38, std::numeric_limits<float>::lowest());
    EXPECT_FLOAT_EQ(1.4012985e-45, std::numeric_limits<float>::denorm_min());
    EXPECT_FLOAT_EQ(1.1920929e-07, std::numeric_limits<float>::epsilon());

    EXPECT_DOUBLE_EQ(2.2250738585072014e-308, std::numeric_limits<double>::min());
    EXPECT_DOUBLE_EQ(1.7976931348623157e+308, std::numeric_limits<double>::max());
    EXPECT_DOUBLE_EQ(-1.7976931348623157e+308, std::numeric_limits<double>::lowest());
    EXPECT_DOUBLE_EQ(4.9406564584124654e-324, std::numeric_limits<double>::denorm_min());
    EXPECT_DOUBLE_EQ(2.2204460492503131e-16, std::numeric_limits<double>::epsilon());

    EXPECT_TRUE(std::numeric_limits<char>::is_signed && !std::numeric_limits<unsigned char>::is_signed);
}

#endif