#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct HeadObjectRequest
        {
            std::string bucket;                       // URI: Bucket
            std::string key;                          // URI: Key
            s3::base::OptStr ifMatch;                 // Header: If-Match
            s3::base::OptStr ifModifiedSince;         // Header: If-Modified-Since
            s3::base::OptStr ifNoneMatch;             // Header: If-None-Match
            s3::base::OptStr ifUnmodifiedSince;       // Header: If-Unmodified-Since
            s3::base::OptStr range;                   // Header: Range
            s3::base::OptStr versionId;               // Query String: versionId
            s3::base::OptI64 partNumber;              // Query String: partNumber
            s3::base::OptStr amzSseCustomerAlgorithm; // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKey;       // Header: x-amz-server-side-encryption-customer-key
            s3::base::OptStr amzSseCustomerKeyMd5;    // Header: x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr amzRequestPayer;         // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;  // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzChecksumMode;         // Header: x-amz-checksum-mode
        };

    } // namespace model
} // namespace s3