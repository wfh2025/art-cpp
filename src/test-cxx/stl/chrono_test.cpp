#include <chrono>
#include <string>

#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(std_chrono, 001)
{
    auto asString = [](const std::chrono::system_clock::time_point& tp) -> std::string {
        std::time_t t = std::chrono::system_clock::to_time_t(tp);
        std::string ts = std::ctime(&t);
        ts.resize(ts.size() - 1);
        return ts;
    };
    EXPECT_EQ(asString(std::chrono::system_clock::time_point{}), "Thu Jan  1 08:00:00 1970");
    (void)asString(std::chrono::system_clock::now());
    EXPECT_EQ(asString(std::chrono::system_clock::time_point::min()), "Mon Dec 22 04:04:49     -290308");
    EXPECT_EQ(asString(std::chrono::system_clock::time_point::max()), "Sun Jan 10 12:00:54     294247");

    typedef std::chrono::duration<int, std::ratio<3600 * 24>> Days;
    std::chrono::time_point<std::chrono::system_clock> tp;
    EXPECT_EQ(asString(tp), "Thu Jan  1 08:00:00 1970");

    // 增加了的时间
    tp += Days(1) + std::chrono::hours(23) + std::chrono::minutes(55);
    EXPECT_EQ(asString(tp), "Sat Jan  3 07:55:00 1970");

    // 差异: 分钟
    auto diff = tp - std::chrono::system_clock::time_point();
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::minutes>(diff).count(), 2875);

    // 差异: 天
    Days days = std::chrono::duration_cast<Days>(diff);
    EXPECT_EQ(days.count(), 1);

    tp -= std::chrono::hours(24 * 365);
    EXPECT_EQ(asString(tp), "Fri Jan  3 07:55:00 1969");

    tp -= std::chrono::duration<int, std::ratio<3600 * 24 * 365>>(50);
    EXPECT_EQ(asString(tp), "Thu Jan 16 07:55:00 1919");

    tp -= std::chrono::duration<int, std::ratio<3600 * 24 * 365>>(50);
    EXPECT_EQ(asString(tp), "Wed Jan 27 08:00:43 1869");
}

TEST(std_chrono_steady_clock, 001)
{
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    long long d0 = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    std::chrono::duration<double> d1 = endTime - startTime;
    SPDLOG_INFO("interval: {}", d0);
}
#endif
