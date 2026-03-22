#pragma once

namespace s3
{
    namespace model
    {
        enum class ChecksumAlgorithm
        {
            NotSet,
            CRC32,
            CRC32C,
            SHA1,
            SHA256,
            CRC64NVME
        };
    }
} // namespace s3
