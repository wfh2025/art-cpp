#pragma once
#include <string>

#include "CommonPrefix.hpp"
#include "Object.hpp"
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct ListObjectsResult
        {
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
            s3::base::OptBool isTruncated;      // Body: isTruncated
            s3::base::OptStr marker;            // Body: isTruncated
            s3::base::OptStr nextMarker;        // Body: nextMarker
            std::vector<Object> contents;       // Body: contents
            s3::base::OptStr name;
            s3::base::OptStr prefix;
            s3::base::OptStr delimiter;
            s3::base::OptI64 maxKeys;
            std::vector<CommonPrefix> commonPrefixes;
            s3::base::OptStr encodingType;
        };
    } // namespace model
} // namespace s3