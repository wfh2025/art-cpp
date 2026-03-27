#include <ratio>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"
#ifdef RUN_ALL_TEST_CASE
TEST(std_ratio, 001)
{
    using r1 = std::ratio<4, 6>;
    EXPECT_TRUE(r1::num == 2 && r1::den == 3);

    using r2 = std::ratio<4>;
    EXPECT_TRUE(r2::num == 4 && r2::den == 1);

    using r3 = std::ratio<4, 1>;
    EXPECT_TRUE(r3::num == 4 && r3::den == 1);

    using r4 = std::ratio<1, 3>;
    using r5 = std::ratio<1, 6>;
    using sum = std::ratio_add<r4, r5>;
    EXPECT_TRUE(sum::num == 1 && sum::den == 2);

    std::ratio<0> zero;
    EXPECT_TRUE(zero.num == 0 && zero.den == 1);

    std::ratio<0, 1> zero2;
    EXPECT_TRUE(zero2.num == 0 && zero2.den == 1);

    typedef std::ratio<25, 15> AlsoFiveThirds;
    EXPECT_TRUE(AlsoFiveThirds::num == 5 && AlsoFiveThirds::den == 3);

    std::ratio<25, 15> val1;
    EXPECT_TRUE(val1.num == 5 && val1.den == 3);

    EXPECT_TRUE((std::ratio_equal<std::ratio_add<std::ratio<1, 3>, std::ratio<1, 6>>, std::ratio<1, 2>>::value));
    EXPECT_TRUE((std::ratio_equal<std::ratio_subtract<std::ratio<1, 3>, std::ratio<1, 6>>, std::ratio<1, 6>>::value));
    EXPECT_TRUE((std::ratio_equal<std::ratio_multiply<std::ratio<2, 3>, std::ratio<3, 4>>, std::ratio<6, 12>>::value));
    EXPECT_TRUE((std::ratio_equal<std::ratio_divide<std::ratio<1, 2>, std::ratio<2, 3>>, std::ratio<3, 4>>::value));
    EXPECT_TRUE((std::ratio_less<std::ratio<1, 3>, std::ratio<1, 2>>::value));
    EXPECT_TRUE((std::ratio_greater<std::ratio<1, 2>, std::ratio<1, 3>>::value));
    EXPECT_TRUE((std::ratio_greater_equal<std::ratio<1, 2>, std::ratio<1, 2>>::value));
    EXPECT_TRUE((std::ratio_less_equal<std::ratio<1, 2>, std::ratio<1, 2>>::value));
}
#endif