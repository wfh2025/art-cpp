#include <future>
#include <ios>
#include <system_error>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "s3/aws_s3.hpp"
#include "ut_config.h"

TEST(buildListObjectsResultToXml, 001)
{
    auto output = s3::ListObjectsResult{};
    output.delimiter = "/";
    output.encodingType = "url";
    output.isTruncated = true;
    output.marker = "mk";
    output.maxKeys = 1000;
    output.name = "quotes";
    output.nextMarker = "nm";
    output.prefix = "N";

    auto ct0 = s3::ListObjectsResult::Content{};
    ct0.checksumAlgorithm = "cksa0";
    ct0.checksumType = "ckst0";
    ct0.eTag = "etag0";
    ct0.key = "key0";
    ct0.lastModified = "lastModify0";
    ct0.owner.displayName = "ct0.o.d0";
    ct0.owner.id = "ct0.o.id0";
    ct0.restoreStatus.isRestoreInProgress = true;
    ct0.restoreStatus.restoreExpiryDate = "ct0.rs.re0";
    ct0.size = 5;
    ct0.storageClass = "standrad";
    ct0.restoreStatus.isRestoreInProgress = true;
    ct0.restoreStatus.restoreExpiryDate = "xxx";
    output.contents.emplace_back(ct0);

    auto ct1 = s3::ListObjectsResult::Content{};
    ct1.checksumAlgorithm = "cksa1";
    ct1.checksumType = "ckst1";
    ct1.eTag = "etag1";
    ct1.key = "key1";
    ct1.lastModified = "lastModify1";
    ct1.owner.displayName = "ct1.o.d";
    ct1.owner.id = "ct1.o.id1";
    ct1.restoreStatus.isRestoreInProgress = true;
    ct1.restoreStatus.restoreExpiryDate = "ct1.rs.re";
    ct1.size = 6;
    ct1.storageClass = "archive";
    ct1.restoreStatus.isRestoreInProgress = false;
    ct1.restoreStatus.restoreExpiryDate = "yyy";
    output.contents.emplace_back(ct1);

    std::string str = s3::buildListObjectsResultToXml(output);
    std::cout << str;
}

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