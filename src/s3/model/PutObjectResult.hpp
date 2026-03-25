#pragma once

#include "ChecksumType.hpp"
#include "RequestCharged.hpp"
#include "ServerSideEncryption.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        // https://github.com/aws/aws-sdk-cpp/blob/main/generated/src/aws-cpp-sdk-s3/include/aws/s3/model/PutObjectResult.h
        struct PutObjectResult
        {
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
            s3::base::OptStr sSECustomerAlgorithm;
            s3::base::OptStr sSECustomerKeyMD5;
            s3::base::OptStr sSEKMSKeyId;
            s3::base::OptStr sSEKMSEncryptionContext;
            s3::base::OptBool bucketKeyEnabled;
            s3::base::OptI64 size;
            RequestCharged requestCharged;
            s3::base::OptStr requestId;
        };
    } // namespace model
} // namespace s3