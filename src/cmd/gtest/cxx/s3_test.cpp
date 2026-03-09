#include <future>
#include <ios>
#include <system_error>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "s3/aws_s3.hpp"
#include "ut_config.h"
#ifdef RUN_ALL_TEST_CASE
TEST(timeToISO8601, 001)
{
    std::string str = "";
    std::chrono::system_clock::time_point tp0 = std::chrono::system_clock::now();
    str = s3::timeToISO8601(tp0);

    std::chrono::system_clock::time_point tp1(std::chrono::milliseconds(1698706800123));
    str = s3::timeToISO8601(tp1);
    std::cout << str << std::endl;
}


#endif