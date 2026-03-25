#pragma once

#include "RequestCharged.hpp"
#include "ServerSideEncryption.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct UploadPartResult
        {
            ServerSideEncryption serverSideEncryption;
            s3::base::OptStr eTag;
            s3::base::OptStr checksumCRC32;
            s3::base::OptStr checksumCRC32C;
            s3::base::OptStr checksumCRC64NVME;
            s3::base::OptStr checksumSHA1;
            s3::base::OptStr checksumSHA256;
            s3::base::OptStr sSECustomerAlgorithm;
            s3::base::OptStr sSECustomerKeyMD5;
            s3::base::OptStr sSEKMSKeyId;
            s3::base::OptBool bucketKeyEnabled;
            RequestCharged requestCharged;
            s3::base::OptStr requestId;
        };
    } // namespace model
} // namespace s3