#pragma once
#include <string>

#include "CommonPrefix.hpp"
#include "DeleteMarkerEntry.hpp"
#include "ObjectVersion.hpp"
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct ListObjectVersionsResult
        {
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
            s3::base::OptBool isTruncated;      // Body
            s3::base::OptStr keyMarker;         // Body
            s3::base::OptStr versionIdMarker;
            s3::base::OptStr nextKeyMarker;
            s3::base::OptStr nextVersionIdMarker;
            std::vector<ObjectVersion> versions;
            std::vector<DeleteMarkerEntry> deleteMarkers;
            s3::base::OptStr name;
            s3::base::OptStr prefix;
            s3::base::OptStr delimiter;
            s3::base::OptI64 maxKeys;
            std::vector<CommonPrefix> commonPrefixes;
            s3::base::OptStr encodingType;
        };
    } // namespace model
} // namespace s3