#pragma once
#include <map>
#include <string>
#include <vector>

#include "Tag.hpp"
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct GetObjectTaggingResult
        {
            s3::base::OptStr versionId; // Header: x-amz-version-id
            std::vector<Tag> tagSet;
            std::string requestId;
        };
    } // namespace model
} // namespace s3