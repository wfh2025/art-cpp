#pragma once
#include <string>
#include <vector>

#include "DeletedObject.hpp"
#include "Error.hpp"
#include "RequestCharged.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct DeleteObjectsResult
        {
            std::vector<DeletedObject> deleted;
            RequestCharged requestCharged; // Header: x-amz-request-charged
            std::vector<Error> errors;
            std::string requestId;
        };

    } // namespace model
} // namespace s3