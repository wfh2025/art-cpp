#pragma once

#include <cstdint>
#include <string>

namespace s3
{
    namespace model
    {
        enum class ServerSideEncryption
        {
            NotSet,
            AES256,
            AwsFsx,
            AwsKms,
            AwsKmsDsse,
        };
    } // namespace model
} // namespace s3