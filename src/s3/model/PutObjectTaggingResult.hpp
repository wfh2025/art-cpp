#pragma once

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct PutObjectTaggingResult
        {
            s3::base::OptStr versionId; // Header: x-amz-version-id
            s3::base::OptStr requestId;
        };
    } // namespace model
} // namespace s3