#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct AbortMultipartUploadRequest
        {
            std::string bucket;                       // URI: Bucket
            std::string key;                          // URI: Key
            s3::base::OptStr uploadId;                // Query String: uploadId
            s3::base::OptStr amzRequestPayer;         // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;  // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzIfMatchInitiatedTime; // Header: x-amz-if-match-initiated-time
        };

    } // namespace model
} // namespace s3