#pragma once
#include <map>

#include "ChecksumAlgorithm.hpp"
#include "ObjectCannedACL.hpp"
#include "ObjectLockLegalHoldStatus.hpp"
#include "RequestPayer.hpp"
#include "ServerSideEncryption.hpp"
#include "StorageClass.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {

        struct PutObjectRequest
        {
            s3::base::OptStr bucket;
            s3::base::OptStr cacheControl;
            s3::base::OptStr contentDisposition;
            s3::base::OptStr contentEncoding;
            s3::base::OptStr contentLanguage;
            s3::base::OptI64 contentLength;
            s3::base::OptStr contentMD5;
            ObjectCannedACL aCL;
            ChecksumAlgorithm checksumAlgorithm;
            s3::base::OptStr checksumCRC32;
            s3::base::OptStr checksumCRC32C;
            s3::base::OptStr checksumCRC64NVME;
            s3::base::OptStr checksumSHA1;
            s3::base::OptStr checksumSHA256;
            s3::base::OptStr expires;
            s3::base::OptStr ifMatch;
            s3::base::OptStr ifNoneMatch;
            s3::base::OptStr grantFullControl;
            s3::base::OptStr grantRead;
            s3::base::OptStr grantReadACP;
            s3::base::OptStr grantWriteACP;
            s3::base::OptStr key;
            s3::base::OptI64 writeOffsetBytes;
            std::map<s3::base::OptStr, s3::base::OptStr> metadata;
            ServerSideEncryption serverSideEncryption;
            StorageClass storageClass;
            s3::base::OptStr websiteRedirectLocation;
            s3::base::OptStr sSECustomerAlgorithm;
            s3::base::OptStr sSECustomerKey;
            s3::base::OptStr sSECustomerKeyMD5;
            s3::base::OptStr sSEKMSKeyId;
            s3::base::OptStr sSEKMSEncryptionContext;
            s3::base::OptBool bucketKeyEnabled;
            RequestPayer requestPayer;
            s3::base::OptStr tagging;
            ObjectLockMode objectLockMode;
            s3::base::OptStr objectLockRetainUntilDate;
            ObjectLockLegalHoldStatus objectLockLegalHoldStatus;
            s3::base::OptStr expectedBucketOwner;
        };
    } // namespace model
} // namespace s3