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
        struct ListObjectsRequest
        {
            std::string bucket;                                             // URI: Bucket
            s3::base::OptStr delimiter;                                     // Query String: delimiter
            EncodingType encodingType;                                      // Query String: encoding-type
            s3::base::OptStr marker;                                        // Query String: marker
            s3::base::OptI64 maxKeys;                                       // Query String: max-keys
            s3::base::OptStr prefix;                                        // Query String: prefix
            RequestPayer requestPayer;                                      // Header: x-amz-request-payer
            s3::base::OptStr expectedBucketOwner;                           // Header: x-amz-expected-bucket-owner
            std::vector<OptionalObjectAttributes> optionalObjectAttributes; // Header: x-amz-optional-object-attributes
        };
    } // namespace model
} // namespace s3