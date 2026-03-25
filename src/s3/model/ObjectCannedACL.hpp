#pragma once

namespace s3
{
    namespace model
    {
        enum class ObjectCannedACL
        {
            NotSet,
            private_,
            public_read,
            public_read_write,
            authenticated_read,
            aws_exec_read,
            bucket_owner_read,
            bucket_owner_full_control
        };
    } // namespace model
} // namespace s3