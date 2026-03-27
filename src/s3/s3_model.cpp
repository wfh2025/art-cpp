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

        const char* checksumTypeToString(const ChecksumType checksumType)
        {
            switch (checksumType)
            {
            case ChecksumType::Composite:
                return "COMPOSITE";
            case ChecksumType::FullObject:
                return "FULL_OBJECT";
            default:
                return "notset";
            }
        }

        ChecksumType stringToChecksumType(const std::string& str)
        {
            if (str == "COMPOSITE")
            {
                return ChecksumType::Composite;
            }
            if (str == "FULL_OBJECT")
            {
                return ChecksumType::FullObject;
            }
            return ChecksumType::NotSet;
        }

        const char* requestPayerToString(const RequestPayer requestPayer)
        {
            switch (requestPayer)
            {
            case RequestPayer::Requester:
                return "requester";
            default:
                return "notset";
            }
        }
        RequestPayer stringToRequestPayer(const std::string& str)
        {
            if (str == "requester")
            {
                return RequestPayer::Requester;
            }
            return RequestPayer::NotSet;
        }
    } // namespace model
} // namespace s3