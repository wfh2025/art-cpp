
#pragma once
#include <vector>

#include "s3/model/Owner.hpp"
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct Object
        {
            s3::base::OptStr key;
            s3::base::OptStr lastModified;
            s3::base::OptStr eTag;
            std::vector<std::string> checksumAlgorithm;
            s3::base::OptStr checksumType;
            s3::base::OptI64 size;
            s3::base::OptStr storageClass;
            Owner owner;
            s3::base::OptStr restoreStatus;
        };
    } // namespace model
} // namespace s3