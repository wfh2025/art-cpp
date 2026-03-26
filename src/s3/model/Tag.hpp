#pragma once
#include <string>

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