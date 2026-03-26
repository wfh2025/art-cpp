#pragma once

#include <string>

#include "ChecksumType.hpp"
#include "CompletedMultipartUpload.hpp"
#include "RequestPayer.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct CompleteMultipartUploadRequest
        {
            std::string bucket;
            std::string key;
            std::string uploadId;
            CompletedMultipartUpload multipartUpload;
            s3::base::OptStr checksumCRC32;
            s3::base::OptStr checksumCRC32C;
            s3::base::OptStr checksumCRC64NVME;
            s3::base::OptStr checksumSHA1;
            s3::base::OptStr checksumSHA256;
            ChecksumType checksumType;
            s3::base::OptI64 mpuObjectSize;
            RequestPayer requestPayer;
            s3::base::OptStr expectedBucketOwner;
            s3::base::OptStr ifMatch;
            s3::base::OptStr ifNoneMatch;
            s3::base::OptStr sSECustomerAlgorithm;
            s3::base::OptStr sSECustomerKey;
            s3::base::OptStr sSECustomerKeyMD5;
        };

    } // namespace model
} // namespace s3