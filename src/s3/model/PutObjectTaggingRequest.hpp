#pragma once
#include <string>

#include "ChecksumAlgorithm.hpp"
#include "RequestPayer.hpp"
#include "Tagging.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct PutObjectTaggingRequest
        {
            std::string bucket;                   // URI: Bucket
            std::string key;                      // URI: Key
            s3::base::OptStr versionId;           // Query String: versionId
            s3::base::OptStr contentMD5;          // Header: Content-MD5
            ChecksumAlgorithm checksumAlgorithm;  // Header: x-amz-sdk-checksum-algorithm
            s3::base::OptStr expectedBucketOwner; // Header: x-amz-expected-bucket-owner
            RequestPayer requestPayer;            // Header: x-amz-request-payer
            Tagging tagging;
        };
    } // namespace model
} // namespace s3