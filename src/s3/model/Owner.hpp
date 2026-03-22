#pragma once
#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct Owner
        {
            s3::base::OptStr id;
            s3::base::OptStr displayName;
        };
    } // namespace model
} // namespace s3