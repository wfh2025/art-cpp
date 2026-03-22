#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct DeleteObjectResult
        {
            s3::base::OptBool amzDeleteMarker;  // Header: x-amz-delete-marker
            s3::base::OptStr amzVersionId;      // Header: x-amz-version-id
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
        };
    } // namespace model
} // namespace s3