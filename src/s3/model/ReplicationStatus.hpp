#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        enum class ReplicationStatus
        {
            NotSet,
            Completed,
            Pending,
            Failed,
            Replica
        };

    } // namespace model
} // namespace s3