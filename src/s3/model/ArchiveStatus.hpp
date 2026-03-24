#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        enum class ArchiveStatus
        {
            NotSet,
            ARCHIVE_ACCESS,
            DEEP_ARCHIVE_ACCESS
        };

    } // namespace model
} // namespace s3