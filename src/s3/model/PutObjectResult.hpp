#pragma once
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        // https://github.com/aws/aws-sdk-cpp/blob/main/generated/src/aws-cpp-sdk-s3/include/aws/s3/model/PutObjectResult.h
        struct PutObjectResult
        {
            s3::base::OptStr amzExpiration;           // x-amz-expiration
            s3::base::OptStr eTag;                    // ETag
            s3::base::OptStr amzChecksumCrc32;        // x-amz-checksum-crc32
            s3::base::OptStr amzChecksumCrc32c;       // x-amz-checksum-crc32c
            s3::base::OptStr amzChecksumCrc64nvme;    // x-amz-checksum-crc64nvme
            s3::base::OptStr amzChecksumSha1;         // x-amz-checksum-sha1
            s3::base::OptStr amzChecksumSha256;       // x-amz-checksum-sha256
            s3::base::OptStr amzChecksumType;         // x-amz-checksum-type
            s3::base::OptStr amzServerSideEncryption; // x-amz-server-side-encryption
            s3::base::OptStr amzVersionId;            // x-amz-version-id
            s3::base::OptStr amzSseCustomerAlgorithm; // x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKeyMd5;    // x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr amzSseAwsKmsKeyId;       // x-amz-server-side-encryption-aws-kms-key-id
            s3::base::OptStr amzSseContext;           // x-amz-server-side-encryption-context
            s3::base::OptBool amzSseBucketKeyEnabled; // x-amz-server-side-encryption-bucket-key-enabled
            s3::base::OptI64 amzObjectSize;           // x-amz-object-size
            s3::base::OptStr amzRequestCharged;       // x-amz-request-charged
        };
    } // namespace model
} // namespace s3