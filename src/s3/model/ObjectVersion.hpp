#pragma once
#include <string>
#include <vector>

#include "Owner.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct ObjectVersion
        {
            std::string eTag;
            std::vector<std::string> checksumAlgorithm;
            s3::base::OptStr checksumType;
            s3::base::OptI64 size;
            s3::base::OptStr storageClass;
            s3::base::OptStr key;
            s3::base::OptStr versionId;
            s3::base::OptBool isLatest;
            s3::base::OptStr lastModified;
            Owner owner;
            s3::base::OptStr restoreStatus;
        };
    } // namespace model
} // namespace s3