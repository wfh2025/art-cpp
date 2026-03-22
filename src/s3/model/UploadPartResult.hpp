#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {

        struct UploadPartResult
        {
            s3::base::OptStr amzServerSideEncryption; // Header: x-amz-server-side-encryption
            std::string eTag;                         // Header: ETag
            s3::base::OptStr amzChecksumCrc32;        // Header: x-amz-checksum-crc32
            s3::base::OptStr amzChecksumCrc32c;       // Header: x-amz-checksum-crc32c
            s3::base::OptStr amzChecksumCrc64nvme;    // Header: x-amz-checksum-crc64nvme
            s3::base::OptStr amzChecksumSha1;         // Header: x-amz-checksum-sha1
            s3::base::OptStr amzChecksumSha256;       // Header: x-amz-checksum-sha256
            s3::base::OptStr amzSseCustomerAlgorithm; // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKeyMd5;    // Header: x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr amzSseAwsKmsKeyId;       // Header: x-amz-server-side-encryption-aws-kms-key-id
            s3::base::OptStr amzRequestCharged;       // Header: x-amz-request-charged
        };
    } // namespace model
} // namespace s3