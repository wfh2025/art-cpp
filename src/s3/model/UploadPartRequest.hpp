#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct UploadPartRequest
        {
            std::string bucket;                       // URI: Bucket
            std::string key;                          // URI: Key
            int64_t partNumber;                       // Query String: partNumber
            std::string uploadId;                     // Query String: uploadId
            s3::base::OptI64 contentLength;           // Header: Content-Length
            s3::base::OptStr contentMD5;              // Header: Content-MD5
            s3::base::OptStr amzSdkChecksumAlgorithm; // Header: x-amz-sdk-checksum-algorithm
            s3::base::OptStr amzChecksumCrc32;        // Header: x-amz-checksum-crc32
            s3::base::OptStr amzChecksumCrc32c;       // Header: x-amz-checksum-crc32c
            s3::base::OptStr amzChecksumCrc64nvme;    // Header: x-amz-checksum-crc64nvme
            s3::base::OptStr amzChecksumSha1;         // Header: x-amz-checksum-sha1
            s3::base::OptStr amzChecksumSha256;       // Header: x-amz-checksum-sha256
            s3::base::OptStr amzExpectedBucketOwner;  // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzRequestPayer;         // Header: x-amz-request-payer
            s3::base::OptStr amzSseCustomerAlgorithm; // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKey;       // Header: x-amz-server-side-encryption-customer-key
            s3::base::OptStr amzSseCustomerKeyMd5;    // Header: x-amz-server-side-encryption-customer-key-MD5
            std::string body;                         // Body: Part data (binary payload)
        };
    } // namespace model
} // namespace s3