#pragma once
#include <string>

#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct Part
        {
            s3::base::OptI64 partNumber;
            s3::base::OptStr lastModified;
            s3::base::OptStr eTag;
            s3::base::OptI64 size;
            s3::base::OptStr checksumCRC32;
            s3::base::OptStr checksumCRC32C;
            s3::base::OptStr checksumCRC64NVME;
            s3::base::OptStr checksumSHA1;
            s3::base::OptStr checksumSHA256;
        };
    } // namespace model
} // namespace s3