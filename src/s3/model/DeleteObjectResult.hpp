#pragma once

#include "RequestCharged.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct DeleteObjectResult
        {
            s3::base::OptBool deleteMarker; // Header: x-amz-delete-marker
            s3::base::OptStr versionId;     // Header: x-amz-version-id
            RequestCharged requestCharged;  // Header: x-amz-request-charged
        };
    } // namespace model
} // namespace s3