#pragma once

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