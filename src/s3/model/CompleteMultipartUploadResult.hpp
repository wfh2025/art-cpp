#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct CompleteMultipartUploadResult
        {
            s3::base::OptStr amzExpiration;           // Header: x-amz-expiration
            s3::base::OptStr amzServerSideEncryption; // Header: x-amz-server-side-encryption
            s3::base::OptStr amzVersionId;            // Header: x-amz-version-id
            s3::base::OptStr amzSseAwsKmsKeyId;       // Header: x-amz-server-side-encryption-aws-kms-key-id
            s3::base::OptBool amzSseBucketKeyEnabled; // Header: x-amz-server-side-encryption-bucket-key-enabled
            s3::base::OptStr amzRequestCharged;       // Header: x-amz-request-charged
            s3::base::OptStr location;                // Body
            std::string eTag;                         // Body
            s3::base::OptStr checksumCrc32;           // Body
            s3::base::OptStr checksumCrc32c;          // Body
            s3::base::OptStr checksumCrc64nvme;       // Body
            s3::base::OptStr checksumSha1;            // Body
            s3::base::OptStr checksumSha256;          // Body
            s3::base::OptStr checksumType;            // Body
        };
    } // namespace model
} // namespace s3