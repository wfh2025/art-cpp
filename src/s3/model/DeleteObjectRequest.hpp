#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct DeleteObjectRequest
        {
            std::string bucket;                             // URI: Bucket
            std::string key;                                // URI: Key
            s3::base::OptStr versionId;                     // Query String: versionId
            s3::base::OptStr mfa;                           // Header: x-amz-mfa
            s3::base::OptBool amzBypassGovernanceRetention; // Header: x-amz-bypass-governance-retention
            s3::base::OptStr amzRequestPayer;               // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;        // Header: x-amz-expected-bucket-owner
            s3::base::OptStr ifMatch;                       // Header: If-Match
            s3::base::OptStr amzIfMatchLastModifiedTime;    // Header: x-amz-if-match-last-modified-time
            s3::base::OptStr amzIfMatchSize;                // Header: x-amz-if-match-size
        };

    } // namespace model
} // namespace s3