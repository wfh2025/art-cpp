#include <future>
#include <ios>
#include <system_error>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "s3/aws_s3.hpp"
#include "ut_config.h"

#ifdef RUN_ALL_TEST_CASE
TEST(RestfulErrorResponseBodyBuilder, 001)
{
    auto builder = s3::RestfulErrorResponseBodyBuilder::create();
    builder.kv("Code", "NoSuchKey");
    builder.kvMap({
        {"Message", "The resource you requested does not exist"},
        {"Resource", "/mybucket/myfoto.jpg"},
        {"RequestId", "4442587FB7D0A2F9"},
    });
    std::string xml = builder.toXml();
    std::cout << xml;
}

TEST(S3ErrorCode, 001)
{
    std::error_code ec0 = s3::S3Error::AccessDenied;
    EXPECT_EQ(static_cast<int>(s3::S3Error::AccessDenied), 2);
    EXPECT_EQ(s3::make_error_code(s3::S3Error::AccessDenied).value(), 2);
    EXPECT_EQ(s3::make_error_code(s3::S3Error::AccessDenied).category(), s3::s3_error_category());
}
#endif