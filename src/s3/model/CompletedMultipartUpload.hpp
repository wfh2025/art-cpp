#pragma once
#include <vector>

#include "CompletedPart.hpp"

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