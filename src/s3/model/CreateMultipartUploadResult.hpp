#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct CreateMultipartUploadResult
        {
            s3::base::OptStr amzAbortDate;            // Header: x-amz-abort-date
            s3::base::OptStr amzAbortRuleId;          // Header: x-amz-abort-rule-id
            s3::base::OptStr amzServerSideEncryption; // Header: x-amz-server-side-encryption
            s3::base::OptStr amzSseCustomerAlgorithm; // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKeyMd5;    // Header: x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr amzSseAwsKmsKeyId;       // Header: x-amz-server-side-encryption-aws-kms-key-id
            s3::base::OptStr amzSseContext;           // Header: x-amz-server-side-encryption-context
            s3::base::OptBool amzSseBucketKeyEnabled; // Header: x-amz-server-side-encryption-bucket-key-enabled
            s3::base::OptStr amzRequestCharged;       // Header: x-amz-request-charged
            s3::base::OptStr amzChecksumAlgorithm;    // Header: x-amz-checksum-algorithm
            s3::base::OptStr amzChecksumType;         // Header: x-amz-checksum-type
            std::string uploadId;                     // Body
        };
    } // namespace model
} // namespace s3