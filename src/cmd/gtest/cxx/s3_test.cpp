#include "s3/aws_s3.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <future>
#include <ios>
#include <system_error>

TEST(S3ErrorCode, 001)
{
    std::error_code ec0 = s3::S3Error::AccessDenied;
    EXPECT_EQ(static_cast<int>(s3::S3Error::AccessDenied), 2);
    EXPECT_EQ(s3::make_error_code(s3::S3Error::AccessDenied).value(), 2);
    EXPECT_EQ(s3::make_error_code(s3::S3Error::AccessDenied).category(), s3::s3_error_category());
}