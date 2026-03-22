#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct PutObjectTaggingRequest
        {
            std::string bucket;                       // URI: Bucket
            std::string key;                          // URI: Key
            s3::base::OptStr versionId;               // Query String: versionId
            s3::base::OptStr contentMD5;              // Header: Content-MD5
            s3::base::OptStr amzChecksumAlgorithm;    // Header: x-amz-checksum-algorithm
            s3::base::OptStr amzSdkChecksumAlgorithm; // Header: x-amz-sdk-checksum-algorithm
            s3::base::OptStr amzExpectedBucketOwner;  // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzRequestPayer;         // Header: x-amz-request-payer
            std::string body;                         // Body: Tagging XML
        };
    } // namespace model
} // namespace s3