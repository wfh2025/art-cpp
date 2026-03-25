#pragma once
#include <string>

#include "RequestPayer.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct ListPartsRequest
        {
            std::string bucket;                    // URI: Bucket
            std::string key;                       // URI: Key
            s3::base::OptI64 maxParts;             // Query String: max-parts
            s3::base::OptI64 partNumberMarker;     // Query String: part-number-marker
            std::string uploadId;                  // Query String: uploadId
            RequestPayer requestPayer;             // Header: x-amz-request-payer
            s3::base::OptStr expectedBucketOwner;  // Header: x-amz-expected-bucket-owner
            s3::base::OptStr sSECustomerAlgorithm; // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr sSECustomerKey;       // Header: x-amz-server-side-encryption-customer-key
            s3::base::OptStr sSECustomerKeyMd5;    // Header: x-amz-server-side-encryption-customer-key-MD5
        };
    } // namespace model
} // namespace s3