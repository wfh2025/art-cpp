#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "spdlog/spdlog.h"

static void initLog()
{
    /**
     * 引入LOG,解决cout在多线程情况下并发错乱问题
     */
    // spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%P] [%t] [%s:%#] [%^%l%$] %v");
    spdlog::set_pattern("%s:%#    %v");
    spdlog::set_level(spdlog::level::debug);
}
int main(int argc, char** argv)
{
    initLog();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}