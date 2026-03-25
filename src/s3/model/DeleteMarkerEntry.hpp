#pragma once

#include "Owner.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct DeleteMarkerEntry
        {
            Owner owner;
            s3::base::OptStr key;
            s3::base::OptStr versionId;
            s3::base::OptBool isLatest;
            s3::base::OptStr lastModified;
        };
    } // namespace model
} // namespace s3