#pragma once

#include <vector>

#include "Tag.hpp"

namespace s3
{
    namespace model
    {
        struct Tagging
        {
            std::vector<Tag> tagSet;
        };
    } // namespace model
} // namespace s3