#pragma once
#include <string>
#include <vector>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct Tag
        {
            std::string key;
            std::string value;
        };
    } // namespace model
} // namespace s3