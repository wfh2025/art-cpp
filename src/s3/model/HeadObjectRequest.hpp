#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct HeadObjectRequest
        {
            std::string bucket;                    // URI: Bucket
            std::string key;                       // URI: Key
            s3::base::OptStr ifMatch;              // Header: If-Match
            s3::base::OptStr ifModifiedSince;      // Header: If-Modified-Since
            s3::base::OptStr ifNoneMatch;          // Header: If-None-Match
            s3::base::OptStr ifUnmodifiedSince;    // Header: If-Unmodified-Since
            s3::base::OptStr range;                // Header: Range
            s3::base::OptStr versionId;            // Query String: versionId
            s3::base::OptI64 partNumber;           // Query String: partNumber
            s3::base::OptStr sSECustomerAlgorithm; // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr sSECustomerKey;       // Header: x-amz-server-side-encryption-customer-key
            s3::base::OptStr sSECustomerKeyMd5;    // Header: x-amz-server-side-encryption-customer-key-MD5
            RequestPayer requestPayer;             // Header: x-amz-request-payer
            s3::base::OptStr expectedBucketOwner;  // Header: x-amz-expected-bucket-owner
            ChecksumMode checksumMode;             // Header: x-amz-checksum-mode
            s3::base::OptStr responseCacheControl;
            s3::base::OptStr responseContentDisposition;
            s3::base::OptStr responseContentEncoding;
            s3::base::OptStr responseContentLanguage;
            s3::base::OptStr responseContentType;
            s3::base::OptStr responseExpires;
        };

    } // namespace model
} // namespace s3