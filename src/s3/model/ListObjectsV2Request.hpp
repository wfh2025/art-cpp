#pragma once
#include <string>
#include <vector>

#include "EncodingType.hpp"
#include "OptionalObjectAttributes.hpp"
#include "RequestPayer.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct ListObjectsV2Request
        {
            std::string bucket;                                             // URI: Bucket
            s3::base::OptStr listType;                                      // Query String: list-type
            s3::base::OptStr continuationToken;                             // Query String: continuation-token
            s3::base::OptStr delimiter;                                     // Query String: delimiter
            EncodingType encodingType;                                      // Query String: encoding-type
            s3::base::OptBool fetchOwner;                                   // Query String: fetch-owner
            s3::base::OptI64 maxKeys;                                       // Query String: max-keys
            s3::base::OptStr prefix;                                        // Query String: prefix
            s3::base::OptStr startAfter;                                    // Query String: start-after
            RequestPayer requestPayer;                                      // Header: x-amz-request-payer
            s3::base::OptStr expectedBucketOwner;                           // Header: x-amz-expected-bucket-owner
            std::vector<OptionalObjectAttributes> optionalObjectAttributes; // Header: x-amz-optional-object-attributes
        };
    } // namespace model
} // namespace s3