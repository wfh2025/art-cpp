#pragma once

#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct ObjectIdentifier
        {
            s3::base::OptStr eTag;
            s3::base::OptStr key;
            s3::base::OptStr lastModifiedTime;
            s3::base::OptI64 size;
            s3::base::OptStr versionId;
        };
    } // namespace model
} // namespace s3