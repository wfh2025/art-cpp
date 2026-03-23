#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct CompletedPart
        {
            std::string eTag;
            s3::base::OptStr checksumCRC32;
            s3::base::OptStr checksumCRC32C;
            s3::base::OptStr checksumCRC64NVME;
            s3::base::OptStr checksumSHA1;
            s3::base::OptStr checksumSHA256;
            int64_t partNumber;
        };
    } // namespace model
} // namespace s3
