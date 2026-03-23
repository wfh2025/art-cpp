#pragma once
#include <string>
#include <vector>

#include "CompletedPart.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct CompletedMultipartUpload
        {
            std::vector<CompletedPart> parts;
        };
    } // namespace model
} // namespace s3