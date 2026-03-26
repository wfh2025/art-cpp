#pragma once
#include <string>

#include "ChecksumType.hpp"
#include "RequestCharged.hpp"
#include "ServerSideEncryption.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct CompleteMultipartUploadResult
        {
            s3::base::OptStr location;
            s3::base::OptStr bucket;
            s3::base::OptStr key;
            s3::base::OptStr expiration;
            s3::base::OptStr eTag;
            s3::base::OptStr checksumCRC32;
            s3::base::OptStr checksumCRC32C;
            s3::base::OptStr checksumCRC64NVME;
            s3::base::OptStr checksumSHA1;
            s3::base::OptStr checksumSHA256;
            ChecksumType checksumType;
            ServerSideEncryption serverSideEncryption;
            s3::base::OptStr versionId;
            s3::base::OptStr sSEKMSKeyId;
            s3::base::OptBool bucketKeyEnabled;
            RequestCharged requestCharged;
            s3::base::OptStr requestId;
        };
    } // namespace model
} // namespace s3