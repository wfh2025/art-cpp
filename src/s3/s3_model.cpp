#include "s3_model.hpp"

namespace s3
{
    namespace model
    {
        const char* storageClassToString(const StorageClass storageClass)
        {
            switch (storageClass)
            {
            case StorageClass::Standard:
                return "standard";
            case StorageClass::Archive:
                return "archive";
            default:
                return "notset";
            }
        }

        StorageClass stringToStorageClass(const std::string& str)
        {
            if (str == "standard")
            {
                return StorageClass::Standard;
            }
            if (str == "archive")
            {
                return StorageClass::Archive;
            }
            return StorageClass::NotSet;
        }
    } // namespace model
} // namespace s3