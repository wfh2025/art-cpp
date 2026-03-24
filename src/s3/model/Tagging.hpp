#pragma once
#include <string>
#include <vector>

#include "Tag.hpp"
#include "s3/s3_base.hpp"
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