#pragma once
#include <string>
#include <vector>

#include "ChecksumAlgorithm.hpp"
#include "ChecksumType.hpp"
#include "Initiator.hpp"
#include "Owner.hpp"
#include "StorageClass.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct MultipartUpload
        {
            s3::base::OptStr uploadId;
            s3::base::OptStr key;
            s3::base::OptStr initiated;
            StorageClass storageClass;
            Owner owner;
            Initiator initiator;
            ChecksumAlgorithm checksumAlgorithm;
            ChecksumType checksumType;
        };

    } // namespace model
} // namespace s3