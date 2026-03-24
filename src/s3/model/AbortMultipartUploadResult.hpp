#pragma once
#include <string>

#include "RequestCharged.hpp"
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct AbortMultipartUploadResult
        {
            model::RequestCharged requestCharged; // Header: x-amz-request-charged
            s3::base::OptStr requestId;
        };
    } // namespace model
} // namespace s3