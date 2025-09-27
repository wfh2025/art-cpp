#include "absl/strings/str_cat.h"
#include "ut_config.h"
#include "gtest/gtest.h"
#include <iostream>

#ifdef RUN_ALL_TEST_CASE
TEST(StrCat, 001)
{
    std::string name = "Alice";
    int age = 25;
    std::string output = absl::StrCat("Name: ", name, ", Age: ", age);
    EXPECT_EQ(output, "Name: Alice, Age: 25");
}

#endif