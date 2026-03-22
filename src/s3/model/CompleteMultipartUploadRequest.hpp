#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct CompleteMultipartUploadRequest
        {
            std::string bucket;                      // URI: Bucket
            std::string key;                         // URI: Key
            s3::base::OptStr uploadId;               // Query String: uploadId
            s3::base::OptStr ifMatch;                // Header: If-Match
            s3::base::OptStr ifNoneMatch;            // Header: If-None-Match
            s3::base::OptStr amzChecksumCrc32;       // Header: x-amz-checksum-crc32
            s3::base::OptStr amzChecksumCrc32c;      // Header: x-amz-checksum-crc32c
            s3::base::OptStr amzChecksumCrc64nvme;   // Header: x-amz-checksum-crc64nvme
            s3::base::OptStr amzChecksumSha1;        // Header: x-amz-checksum-sha1
            s3::base::OptStr amzChecksumSha256;      // Header: x-amz-checksum-sha256
            s3::base::OptStr amzChecksumType;        // Header: x-amz-checksum-type
            s3::base::OptStr amzMpObjectSize;        // Header: x-amz-mp-object-size
            s3::base::OptStr amzRequestPayer;        // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner; // Header: x-amz-expected-bucket-owner
            std::string body;                        // Body: CompleteMultipartUpload XML
        };

        } // namespace model
} // namespace s3