#pragma once
#include <string>

#include "ChecksumAlgorithm.hpp"
#include "Delete.hpp"
#include "RequestPayer.hpp"
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct DeleteObjectsRequest
        {
            Delete deleteNode;                           // Body: Delete XML node
            std::string bucket;                          // URI: Bucket
            s3::base::OptStr mfa;                        // Header: x-amz-mfa
            RequestPayer requestPayer;                   // Header: x-amz-request-payer
            s3::base::OptStr contentMD5;                 // Header: Content-MD5
            ChecksumAlgorithm checksumAlgorithm;         // Header: x-amz-sdk-checksum-algorithm
            s3::base::OptBool bypassGovernanceRetention; // Header: x-amz-bypass-governance-retention
            s3::base::OptStr expectedBucketOwner;        // Header: x-amz-expected-bucket-owner
        };

    } // namespace model
} // namespace s3