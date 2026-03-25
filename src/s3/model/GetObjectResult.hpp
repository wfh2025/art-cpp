#pragma once
#include <string>

#include "ChecksumType.hpp"
#include "ObjectLockLegalHoldStatus.hpp"
#include "ObjectLockMode.hpp"
#include "ReplicationStatus.hpp"
#include "RequestCharged.hpp"
#include "ServerSideEncryption.hpp"
#include "StorageClass.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct GetObjectResult
        {
            ChecksumType checksumType;
            StorageClass storageClass;
            RequestCharged requestCharged;
            ReplicationStatus replicationStatus;
            ObjectLockMode objectLockMode;
            ObjectLockLegalHoldStatus objectLockLegalHoldStatus;
            ServerSideEncryption serverSideEncryption;
            s3::base::OptBool deleteMarker;
            s3::base::OptStr acceptRanges;
            s3::base::OptStr expiration;
            s3::base::OptStr restore;
            s3::base::OptStr lastModified;
            s3::base::OptI64 contentLength;
            s3::base::OptStr eTag;
            s3::base::OptStr checksumCRC32;
            s3::base::OptStr checksumCRC32C;
            s3::base::OptStr checksumCRC64NVME;
            s3::base::OptStr checksumSHA1;
            s3::base::OptStr checksumSHA256;
            s3::base::OptI64 missingMeta;
            s3::base::OptStr versionId;
            s3::base::OptStr cacheControl;
            s3::base::OptStr contentDisposition;
            s3::base::OptStr contentEncoding;
            s3::base::OptStr contentLanguage;
            s3::base::OptStr contentRange;
            s3::base::OptStr contentType;
            s3::base::OptStr expires;
            s3::base::OptStr websiteRedirectLocation;
            std::map<std::string, std::string> metadata;
            s3::base::OptStr sSECustomerAlgorithm;
            s3::base::OptStr sSECustomerKeyMD5;
            s3::base::OptStr sSEKMSKeyId;
            s3::base::OptBool bucketKeyEnabled;
            s3::base::OptI64 partsCount;
            s3::base::OptI64 tagCount;
            s3::base::OptStr objectLockRetainUntilDate;
            s3::base::OptStr id2;
            s3::base::OptStr requestId;
            s3::base::OptStr expiresString;
        };
    } // namespace model
} // namespace s3