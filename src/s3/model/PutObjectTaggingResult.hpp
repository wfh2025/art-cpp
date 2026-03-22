#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct PutObjectTaggingResult
        {
            s3::base::OptStr amzVersionId; // Header: x-amz-version-id
        };
    } // namespace model
} // namespace s3