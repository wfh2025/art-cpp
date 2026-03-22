#pragma once
#include <map>
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct GetObjectTaggingResult
        {
            s3::base::OptStr amzVersionId;              // Header: x-amz-version-id
            s3::base::OptStr amzRequestCharged;         // Header: x-amz-request-charged
            std::map<std::string, std::string> tagging; // Body: Tagging XML
        };
    } // namespace model
} // namespace s3