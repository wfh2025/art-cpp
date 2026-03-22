#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct DeleteObjectsResult
        {
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
            std::string body;                   // Body: DeleteResult XML
        };

    } // namespace model
} // namespace s3