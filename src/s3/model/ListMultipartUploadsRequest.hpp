#pragma once

#include "EncodingType.hpp"
#include "RequestPayer.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct ListMultipartUploadsRequest
        {
            s3::base::OptStr bucket;
            s3::base::OptStr delimiter;
            EncodingType encodingType;
            s3::base::OptStr keyMarker;
            s3::base::OptI64 maxUploads;
            s3::base::OptStr prefix;
            s3::base::OptStr uploadIdMarker;
            s3::base::OptStr expectedBucketOwner;
            RequestPayer requestPayer;
        };

    } // namespace model
} // namespace s3