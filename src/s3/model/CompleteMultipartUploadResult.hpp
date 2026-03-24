#pragma once
#include <string>

#include "RequestCharged.hpp"
#include "ServerSideEncryption.hpp"
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct CompleteMultipartUploadResult
        {
            s3::base::OptStr expiration;                          // Header: x-amz-expiration
            s3::model::ServerSideEncryption serverSideEncryption; // Header: x-amz-server-side-encryption
            s3::base::OptStr versionId;                           // Header: x-amz-version-id
            s3::base::OptStr sSEKMSKeyId;                         // Header: x-amz-server-side-encryption-aws-kms-key-id
            s3::model::RequestCharged requestCharged;             // Header: x-amz-request-charged
            s3::base::OptBool bucketKeyEnabled;                   // Header: x-amz-server-side-encryption-bucket-key-enabled
            s3::base::OptStr location;                            // Body
            std::string bucket;                                   // Body
            std::string key;                                      // Body
            std::string eTag;                                     // Body
            s3::base::OptStr checksumCrc32;                       // Body
            s3::base::OptStr checksumCrc32c;                      // Body
            s3::base::OptStr checksumCrc64nvme;                   // Body
            s3::base::OptStr checksumSha1;                        // Body
            s3::base::OptStr checksumSha256;                      // Body
            s3::model::ChecksumType checksumType;                 // Body
            s3::base::OptStr requestId;
        };
    } // namespace model
} // namespace s3