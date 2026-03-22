#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct AbortMultipartUploadResult
        {
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
        };
    } // namespace model
} // namespace s3