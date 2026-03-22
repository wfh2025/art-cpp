#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct GetObjectTaggingRequest
        {
            std::string bucket;                      // URI: Bucket
            std::string key;                         // URI: Key
            s3::base::OptStr versionId;              // Query String: versionId
            s3::base::OptStr amzExpectedBucketOwner; // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzRequestPayer;        // Header: x-amz-request-payer
        };
    } // namespace model
} // namespace s3