#pragma once
#include <string>

#include "RequestPayer.hpp"
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct AbortMultipartUploadRequest
        {
            std::string bucket;
            std::string key;
            std::string uploadId;
            RequestPayer requestPayer;
            s3::base::OptStr expectedBucketOwner;
            s3::base::OptStr ifMatchInitiatedTime;
        };

    } // namespace model
} // namespace s3