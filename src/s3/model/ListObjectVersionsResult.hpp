#pragma once
#include <string>

#include "CommonPrefix.hpp"
#include "DeleteMarkerEntry.hpp"
#include "EncodingType.hpp"
#include "ObjectVersion.hpp"
#include "RequestCharged.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct ListObjectVersionsResult
        {
            EncodingType encodingType;
            std::vector<ObjectVersion> versions;
            RequestCharged requestCharged; // Header: x-amz-request-charged
            std::vector<CommonPrefix> commonPrefixes;
            std::vector<DeleteMarkerEntry> deleteMarkers;
            s3::base::OptBool isTruncated; // Body
            s3::base::OptStr keyMarker;    // Body
            s3::base::OptStr versionIdMarker;
            s3::base::OptStr nextKeyMarker;
            s3::base::OptStr nextVersionIdMarker;
            s3::base::OptStr name;
            s3::base::OptStr prefix;
            s3::base::OptStr delimiter;
            s3::base::OptI64 maxKeys;
            s3::base::OptStr requestId;
        };
    } // namespace model
} // namespace s3