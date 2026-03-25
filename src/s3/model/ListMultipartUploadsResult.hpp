#pragma once
#include <string>
#include <vector>

#include "CommonPrefix.hpp"
#include "EncodingType.hpp"
#include "MultipartUpload.hpp"
#include "RequestCharged.hpp"
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct ListMultipartUploadsResult
        {
            std::vector<MultipartUpload> uploads;
            std::vector<CommonPrefix> commonPrefixes;
            EncodingType encodingType;
            RequestCharged requestCharged;
            s3::base::OptStr bucket;
            s3::base::OptStr keyMarker;
            s3::base::OptStr uploadIdMarker;
            s3::base::OptStr nextKeyMarker;
            s3::base::OptStr prefix;
            s3::base::OptStr delimiter;
            s3::base::OptStr nextUploadIdMarker;
            s3::base::OptI64 maxUploads;
            s3::base::OptBool isTruncated;
            s3::base::OptStr requestId;
        };

    } // namespace model
} // namespace s3