#pragma once

#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct DeleteObjectTaggingResult
        {
            s3::base::OptStr versionId; // Header: x-amz-version-id
        };
    } // namespace model
} // namespace s3