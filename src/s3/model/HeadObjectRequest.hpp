#pragma once
#include <string>

#include "ChecksumMode.hpp"
#include "RequestPayer.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct HeadObjectRequest
        {
            RequestPayer requestPayer;
            ChecksumMode checksumMode;
            s3::base::OptStr bucket;
            s3::base::OptStr ifMatch;
            s3::base::OptStr ifModifiedSince;
            s3::base::OptStr ifNoneMatch;
            s3::base::OptStr ifUnmodifiedSince;
            s3::base::OptStr key;
            s3::base::OptStr range;
            s3::base::OptStr responseCacheControl;
            s3::base::OptStr responseContentDisposition;
            s3::base::OptStr responseContentEncoding;
            s3::base::OptStr responseContentLanguage;
            s3::base::OptStr responseContentType;
            s3::base::OptStr responseExpires;
            s3::base::OptStr versionId;
            s3::base::OptStr sSECustomerAlgorithm;
            s3::base::OptStr sSECustomerKey;
            s3::base::OptStr sSECustomerKeyMD5;
            s3::base::OptI64 partNumber;
            s3::base::OptStr expectedBucketOwner;
        };

    } // namespace model
} // namespace s3