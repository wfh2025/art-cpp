#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct ListPartsRequest
        {
            std::string bucket;                       // URI: Bucket
            std::string key;                          // URI: Key
            s3::base::OptI64 maxParts;                // Query String: max-parts
            s3::base::OptI64 partNumberMarker;        // Query String: part-number-marker
            std::string uploadId;                     // Query String: uploadId
            s3::base::OptStr amzRequestPayer;         // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;  // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzSseCustomerAlgorithm; // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKey;       // Header: x-amz-server-side-encryption-customer-key
            s3::base::OptStr amzSseCustomerKeyMd5;    // Header: x-amz-server-side-encryption-customer-key-MD5
        };
    } // namespace model
} // namespace s3