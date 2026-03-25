#pragma once
#include <string>

#include "ChecksumAlgorithm.hpp"
#include "ChecksumType.hpp"
#include "ObjectCannedACL.hpp"
#include "ObjectLockLegalHoldStatus.hpp"
#include "ObjectLockMode.hpp"
#include "RequestPayer.hpp"
#include "ServerSideEncryption.hpp"
#include "StorageClass.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct CreateMultipartUploadRequest
        {
            std::string bucket;
            s3::base::OptStr cacheControl;
            s3::base::OptStr contentDisposition;
            s3::base::OptStr contentEncoding;
            s3::base::OptStr contentLanguage;
            s3::base::OptStr contentType;
            s3::base::OptStr expires;
            s3::base::OptStr grantFullControl;
            s3::base::OptStr grantRead;
            s3::base::OptStr grantReadACP;
            s3::base::OptStr grantWriteACP;
            std::string key;
            std::map<std::string, std::string> metadata;
            s3::base::OptStr websiteRedirectLocation;
            s3::base::OptStr sSECustomerAlgorithm;
            s3::base::OptStr sSECustomerKey;
            s3::base::OptStr sSECustomerKeyMD5;
            s3::base::OptStr sSEKMSKeyId;
            s3::base::OptStr sSEKMSEncryptionContext;
            s3::base::OptBool bucketKeyEnabled;
            s3::base::OptStr tagging;
            s3::base::OptStr objectLockRetainUntilDate;
            s3::base::OptStr expectedBucketOwner;
            ObjectCannedACL aCL;
            ServerSideEncryption serverSideEncryption;
            StorageClass storageClass;
            ObjectLockMode objectLockMode;
            RequestPayer requestPayer;
            ChecksumAlgorithm checksumAlgorithm;
            ChecksumType checksumType;
            ObjectLockLegalHoldStatus objectLockLegalHoldStatus;
        };
    } // namespace model
} // namespace s3