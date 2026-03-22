#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct DeleteObjectsRequest
        {
            std::string bucket;                             // URI: Bucket
            s3::base::OptStr contentMD5;                    // Header: Content-MD5
            s3::base::OptStr amzChecksumAlgorithm;          // Header: x-amz-checksum-algorithm
            s3::base::OptStr amzSdkChecksumAlgorithm;       // Header: x-amz-sdk-checksum-algorithm
            s3::base::OptStr mfa;                           // Header: x-amz-mfa
            s3::base::OptBool amzBypassGovernanceRetention; // Header: x-amz-bypass-governance-retention
            s3::base::OptStr amzRequestPayer;               // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;        // Header: x-amz-expected-bucket-owner
            Delete deleteNode;                              // Body: Delete XML node
        };

    } // namespace model
} // namespace s3