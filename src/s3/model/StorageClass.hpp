#pragma once

#include <cstdint>
#include <string>

namespace s3
{
    namespace model
    {
        enum class StorageClass : int32_t
        {
            NotSet,
            Standard,
            Archive,
        };
        const char* storageClassToString(const StorageClass storageClass);
        StorageClass stringToStorageClass(const std::string& str);
    } // namespace model
} // namespace s3