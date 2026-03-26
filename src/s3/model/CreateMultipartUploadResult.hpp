#pragma once
#include <string>

#include "ChecksumAlgorithm.hpp"
#include "ChecksumType.hpp"
#include "RequestCharged.hpp"
#include "ServerSideEncryption.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct CreateMultipartUploadResult
        {
            s3::base::OptStr abortDate;
            s3::base::OptStr abortRuleId;
            s3::base::OptStr bucket;
            s3::base::OptStr key;
            std::string uploadId;
            ServerSideEncryption serverSideEncryption;
            s3::base::OptStr sSECustomerAlgorithm;
            s3::base::OptStr sSECustomerKeyMD5;
            s3::base::OptStr sSEKMSKeyId;
            s3::base::OptStr sSEKMSEncryptionContext;
            s3::base::OptBool bucketKeyEnabled;
            RequestCharged requestCharged;
            ChecksumAlgorithm checksumAlgorithm;
            ChecksumType checksumType;
        };
    } // namespace model
} // namespace s3