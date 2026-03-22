#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct ListObjectVersionsRequest
        {
            std::string bucket;                      // URI: Bucket
            s3::base::OptStr delimiter;              // Query String: delimiter
            s3::base::OptStr encodingType;           // Query String: encoding-type
            s3::base::OptStr keyMarker;              // Query String: key-marker
            s3::base::OptI64 maxKeys;                // Query String: max-keys
            s3::base::OptStr prefix;                 // Query String: prefix
            s3::base::OptStr versionIdMarker;        // Query String: version-id-marker
            s3::base::OptStr amzRequestPayer;        // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner; // Header: x-amz-expected-bucket-owner
        };
    } // namespace model
} // namespace s3