#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(chrono_steady_clock, 001)
{
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    long long d0 = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    std::chrono::duration<double> d1 = endTime - startTime;
    SPDLOG_INFO("interval: {}", d0);
}
#endif
