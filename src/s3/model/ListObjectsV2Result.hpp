#pragma once
#include <string>

#include "CommonPrefix.hpp"
#include "EncodingType.hpp"
#include "Object.hpp"
#include "RequestCharged.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct ListObjectsV2Result
        {
            bool isTruncated;
            std::vector<Object> contents;
            s3::base::OptStr name;
            s3::base::OptStr prefix;
            s3::base::OptStr delimiter;
            s3::base::OptI64 maxKeys;
            std::vector<CommonPrefix> commonPrefixes;
            EncodingType encodingType;
            s3::base::OptI64 keyCount;
            s3::base::OptStr continuationToken;
            s3::base::OptStr nextContinuationToken;
            s3::base::OptStr startAfter;
            RequestCharged requestCharged;
            s3::base::OptStr requestId;
        };
    } // namespace model
} // namespace s3