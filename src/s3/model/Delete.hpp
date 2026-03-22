#pragma once
#include <map>
#include <string>
#include <vector>

#include "ObjectIdentifier.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct Delete
        {
            s3::base::OptBool quiet;
            std::vector<ObjectIdentifier> objects;
        };
    } // namespace model
} // namespace s3