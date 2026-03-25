#pragma once

#include <vector>

#include "ChecksumAlgorithm.hpp"
#include "ChecksumType.hpp"
#include "Initiator.hpp"
#include "Owner.hpp"
#include "Part.hpp"
#include "RequestCharged.hpp"
#include "StorageClass.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct ListPartsResult
        {
            s3::base::OptStr abortDate;
            s3::base::OptStr abortRuleId;
            s3::base::OptStr bucket;
            s3::base::OptStr key;
            s3::base::OptStr uploadId;
            s3::base::OptI64 partNumberMarker;
            s3::base::OptI64 nextPartNumberMarker;
            s3::base::OptI64 maxParts;
            s3::base::OptBool isTruncated;
            std::vector<Part> parts;
            Initiator initiator;
            Owner owner;
            StorageClass storageClass;
            RequestCharged requestCharged;
            ChecksumAlgorithm checksumAlgorithm;
            ChecksumType checksumType;
            s3::base::OptStr requestId;
        };
    } // namespace model
} // namespace s3