#include <future>
#include <ios>
#include <system_error>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "s3/s3_req.hpp"
#include "s3/s3_resp.hpp"
#include "s3/s3_utils.hpp"
#include "spdlog/spdlog.h"
#include "tinyformat/tinyformat.h"
#include "ut_config.h"

TEST(s3_resp_toXml_CreateMultipartUploadResult, 001)
{
    s3::model::CreateMultipartUploadResult res;
    res.abortDate = "abortDate";
    res.abortRuleId = "abortRuleId";
    res.bucket = "bucket";
    res.bucketKeyEnabled = true;
    res.checksumAlgorithm = s3::model::ChecksumAlgorithm::CRC32C;
    res.checksumType = s3::model::ChecksumType::FullObject;
    res.key = "key";
    res.requestCharged = s3::model::RequestCharged::Requester;
    res.serverSideEncryption = s3::model::ServerSideEncryption::AwsKms;
    res.sSECustomerAlgorithm = "sSECustomerAlgorithm";
    res.uploadId = "uploadId";
    std::string xml = s3::resp::toXml(res);
    std::cout << xml << std::endl;
}

#ifdef RUN_ALL_TEST_CASE
TEST(s3_req_parseDeleteObjectsBodyXml, 001)
{
    const std::string body =
        R"(
<?xml version="1.0" encoding="UTF-8"?>
<Delete
    xmlns="http://s3.amazonaws.com/doc/2006-03-01/">
    <Object>
        <Key>key-1</Key>
        <VersionId>versionId-1</VersionId>
        <ETag>etag-1</ETag>
        <LastModifiedTime>lastModifiedTime-1</LastModifiedTime>
        <Size>100</Size>
    </Object>
    <Object>
        <Key>key-2</Key>
    </Object>
    <Quiet>false</Quiet>
</Delete>           
)";
    s3::model::Delete del;
    del.objects.emplace_back();
    const auto ret = s3::req::parseDeleteObjectsBodyXml(body, del);
    EXPECT_EQ(ret, s3::err::S3ErrorCode::Ok);
    ASSERT_EQ(del.objects.size(), 2U);
    EXPECT_TRUE(del.quiet.has() && (del.quiet.value() == false));
    EXPECT_TRUE(del.objects[0].key.has() && (del.objects[0].key.value() == "key-1"));
    EXPECT_TRUE(del.objects[0].versionId.has() && (del.objects[0].versionId.value() == "versionId-1"));
    EXPECT_TRUE(del.objects[0].eTag.has() && (del.objects[0].eTag.value() == "etag-1"));
    EXPECT_TRUE(del.objects[0].size.has() && (del.objects[0].size.value() == 100));
    EXPECT_TRUE(del.objects[0].lastModifiedTime.has() && (del.objects[0].lastModifiedTime.value() == "lastModifiedTime-1"));

    EXPECT_TRUE(del.objects[1].key.has() && (del.objects[1].key.value() == "key-2"));
    EXPECT_TRUE(!del.objects[1].versionId.has());
    EXPECT_TRUE(!del.objects[1].eTag.has());
    EXPECT_TRUE(!del.objects[1].size.has());
    EXPECT_TRUE(!del.objects[1].lastModifiedTime.has());
}

TEST(s3_req_parsePutObjectTaggingBodyXml, 001)
{
    const std::string body = R"(
<?xml version="1.0" encoding="UTF-8"?>
<Tagging
    xmlns="http://s3.amazonaws.com/doc/2006-03-01/">
    <TagSet>
        <Tag>
            <Key>k1</Key>
            <Value>v1</Value>
        </Tag>
        <Tag>
            <Key>k2</Key>
            <Value>v2</Value>
        </Tag>
    </TagSet>
</Tagging>
)";
    s3::model::Tagging tagging;
    tagging.tagSet.emplace_back();
    tagging.tagSet.back().key = "pre";
    const auto ret = s3::req::parsePutObjectTaggingBodyXml(body, tagging);
    EXPECT_EQ(ret, s3::err::S3ErrorCode::Ok);
    ASSERT_EQ(tagging.tagSet.size(), 2U);
    EXPECT_EQ(tagging.tagSet[0].key, "k1");
    EXPECT_EQ(tagging.tagSet[0].value, "v1");
    EXPECT_EQ(tagging.tagSet[1].key, "k2");
    EXPECT_EQ(tagging.tagSet[1].value, "v2");
}

TEST(s3_req_parseCompleteMultipartUploadBodyXml, 001)
{
    const std::string body = R"(
<?xml version="1.0" encoding="UTF-8"?>
<CompleteMultipartUpload
    xmlns="http://s3.amazonaws.com/doc/2006-03-01/">
    <Part>
        <ETag>etag-1</ETag>
        <PartNumber>1</PartNumber>
        <ChecksumCRC32>crc32-1</ChecksumCRC32>
        <ChecksumCRC32C>crc32c-1</ChecksumCRC32C>
        <ChecksumCRC64NVME>crc64nvme-1</ChecksumCRC64NVME>
        <ChecksumSHA1>sha1-1</ChecksumSHA1>
        <ChecksumSHA256>sha256-1</ChecksumSHA256>
    </Part>
    <Part>
        <ETag>etag-2</ETag>
        <PartNumber>2</PartNumber>
        <ChecksumCRC32>crc32-2</ChecksumCRC32>
        <ChecksumCRC32C>crc32c-2</ChecksumCRC32C>
        <ChecksumCRC64NVME>crc64nvme-2</ChecksumCRC64NVME>
        <ChecksumSHA1>sha1-2</ChecksumSHA1>
        <ChecksumSHA256>sha256-2</ChecksumSHA256>
    </Part>
    <Part>
        <ETag>etag-3</ETag>
        <PartNumber>3</PartNumber>
    </Part>
</CompleteMultipartUpload>
)";

    s3::model::CompletedMultipartUpload uploadParts;
    const auto ret = s3::req::parseCompleteMultipartUploadBodyXml(body, uploadParts);
    EXPECT_EQ(ret, s3::err::S3ErrorCode::Ok);
    EXPECT_EQ(uploadParts.parts.size(), 3U);
    EXPECT_EQ(uploadParts.parts[0].eTag, "etag-1");
    EXPECT_EQ(uploadParts.parts[0].partNumber, 1);
    EXPECT_TRUE((uploadParts.parts[0].checksumCRC32.has()) && (uploadParts.parts[0].checksumCRC32.value() == "crc32-1"));
    EXPECT_TRUE((uploadParts.parts[0].checksumCRC32C.has()) && (uploadParts.parts[0].checksumCRC32C.value() == "crc32c-1"));
    EXPECT_TRUE((uploadParts.parts[0].checksumCRC64NVME.has()) && (uploadParts.parts[0].checksumCRC64NVME.value() == "crc64nvme-1"));
    EXPECT_TRUE((uploadParts.parts[0].checksumSHA1.has()) && (uploadParts.parts[0].checksumSHA1.value() == "sha1-1"));
    EXPECT_TRUE((uploadParts.parts[0].checksumSHA256.has()) && (uploadParts.parts[0].checksumSHA256.value() == "sha256-1"));

    EXPECT_EQ(uploadParts.parts[1].eTag, "etag-2");
    EXPECT_EQ(uploadParts.parts[1].partNumber, 2);
    EXPECT_TRUE((uploadParts.parts[1].checksumCRC32.has()) && (uploadParts.parts[1].checksumCRC32.value() == "crc32-2"));
    EXPECT_TRUE((uploadParts.parts[1].checksumCRC32C.has()) && (uploadParts.parts[1].checksumCRC32C.value() == "crc32c-2"));
    EXPECT_TRUE((uploadParts.parts[1].checksumCRC64NVME.has()) && (uploadParts.parts[1].checksumCRC64NVME.value() == "crc64nvme-2"));
    EXPECT_TRUE((uploadParts.parts[1].checksumSHA1.has()) && (uploadParts.parts[1].checksumSHA1.value() == "sha1-2"));
    EXPECT_TRUE((uploadParts.parts[1].checksumSHA256.has()) && (uploadParts.parts[1].checksumSHA256.value() == "sha256-2"));

    EXPECT_EQ(uploadParts.parts[2].eTag, "etag-3");
    EXPECT_EQ(uploadParts.parts[2].partNumber, 3);
    EXPECT_TRUE((!uploadParts.parts[2].checksumCRC32.has()) && (!uploadParts.parts[2].checksumCRC32C.has()) &&
                (!uploadParts.parts[2].checksumCRC64NVME.has()) && (!uploadParts.parts[2].checksumSHA1.has()) &&
                (!uploadParts.parts[2].checksumSHA256.has()));
}

TEST(s3_base_OptStr, 002)
{
    using s3::base::OptStr;
    {
        SPDLOG_INFO("{:-^80}", "001");
        OptStr op;
        EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "002");
        OptStr op{};
        EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "003");
        // OptStr op(); // 声明
        // EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "004");
        OptStr op = "abc";
        EXPECT_TRUE((op.has() == true) && (op.value() == "abc"));
        op.reset();
        EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "005");
        OptStr op;
        EXPECT_TRUE(op.has() == false);

        op = "5";
        EXPECT_TRUE((op.has() == true) && (op.value() == "5"));

        op = "3";
        EXPECT_TRUE((op.has() == true) && (op.value() == "3"));
    }
    {
        struct S
        {
            OptStr opt;
        };
        SPDLOG_INFO("{:-^80}", "006");
        S s;
        EXPECT_TRUE(s.opt.has() == false);
    }
    {
        struct S
        {
            OptStr opt = "2";
        };
        SPDLOG_INFO("{:-^80}", "007");
        S s;
        EXPECT_TRUE((s.opt.has() == true) && (s.opt.value() == "2"));
    }
    {
        struct S
        {
            OptStr opt{"2"};
        };
        SPDLOG_INFO("{:-^80}", "008");
        S s;
        EXPECT_TRUE((s.opt.has() == true) && (s.opt.value() == "2"));
    }

    int32_t x;
    int64_t y;
}

TEST(s3_base_OptI64, 001)
{
    using s3::base::OptI64;
    {
        SPDLOG_INFO("{:-^80}", "001");
        OptI64 op;
        EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "002");
        OptI64 op{};
        EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "003");
        // 函数声明
        // OptI64 op();
    }
    {
        SPDLOG_INFO("{:-^80}", "004");
        OptI64 op = 4;
        EXPECT_TRUE((op.has() == true) && (op.value() == 4));
        op.reset();
        EXPECT_TRUE(op.has() == false);
    }
    {
        SPDLOG_INFO("{:-^80}", "005");
        OptI64 op;
        EXPECT_TRUE(op.has() == false);

        op = 5;
        EXPECT_TRUE((op.has() == true) && (op.value() == 5));

        op = 3;
        EXPECT_TRUE((op.has() == true) && (op.value() == 3));
    }
    {
        struct S
        {
            OptI64 opt;
        };
        SPDLOG_INFO("{:-^80}", "006");
        S s;
        EXPECT_TRUE(s.opt.has() == false);
    }
    {
        struct S
        {
            OptI64 opt = 2;
        };
        SPDLOG_INFO("{:-^80}", "007");
        S s;
        EXPECT_TRUE((s.opt.has() == true) && (s.opt.value() == 2));
    }
    {
        struct S
        {
            OptI64 opt{2};
        };
        SPDLOG_INFO("{:-^80}", "008");
        S s;
        EXPECT_TRUE((s.opt.has() == true) && (s.opt.value() == 2));
    }
}
#endif