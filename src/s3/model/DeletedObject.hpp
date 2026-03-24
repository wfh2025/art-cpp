#pragma once
#include <string>
#include <vector>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct DeletedObject
        {
            std::string key;
            bool deleteMarker;
            std::string versionId;
            std::string deleteMarkerVersionId;
        };

    } // namespace model
} // namespace s3