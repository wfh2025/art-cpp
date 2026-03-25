#pragma once

#include "ChecksumAlgorithm.hpp"
#include "RequestPayer.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct UploadPartRequest
        {
            s3::base::OptStr bucket;
            s3::base::OptI64 contentLength;
            s3::base::OptStr contentMD5;
            ChecksumAlgorithm checksumAlgorithm;
            s3::base::OptStr checksumCRC32;
            s3::base::OptStr checksumCRC32C;
            s3::base::OptStr checksumCRC64NVME;
            s3::base::OptStr checksumSHA1;
            s3::base::OptStr checksumSHA256;
            s3::base::OptStr key;
            s3::base::OptI64 partNumber;
            s3::base::OptStr uploadId;
            s3::base::OptStr sSECustomerAlgorithm;
            s3::base::OptStr sSECustomerKey;
            s3::base::OptStr sSECustomerKeyMD5;
            RequestPayer requestPayer;
            s3::base::OptStr expectedBucketOwner;
        };
    } // namespace model
} // namespace s3