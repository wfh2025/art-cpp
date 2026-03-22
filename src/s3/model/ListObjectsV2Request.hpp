#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct ListObjectsV2Request
        {
            std::string bucket;                           // URI: Bucket
            s3::base::OptStr listType;                    // Query String: list-type
            s3::base::OptStr continuationToken;           // Query String: continuation-token
            s3::base::OptStr delimiter;                   // Query String: delimiter
            s3::base::OptStr encodingType;                // Query String: encoding-type
            s3::base::OptBool fetchOwner;                 // Query String: fetch-owner
            s3::base::OptI64 maxKeys;                     // Query String: max-keys
            s3::base::OptStr prefix;                      // Query String: prefix
            s3::base::OptStr startAfter;                  // Query String: start-after
            s3::base::OptStr amzRequestPayer;             // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;      // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzOptionalObjectAttributes; // Header: x-amz-optional-object-attributes
        };
    } // namespace model
} // namespace s3