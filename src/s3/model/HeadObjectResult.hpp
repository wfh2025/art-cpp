#pragma once
#include <string>

#include "ArchiveStatus.hpp"
#include "ChecksumType.hpp"
#include "RequestCharged.hpp"
#include "ServerSideEncryption.hpp"
#include "StorageClass.hpp"
#include "s3/s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct HeadObjectResult
        {
            s3::base::OptBool deleteMarker;      // Header: x-amz-delete-marker
            s3::base::OptStr acceptRanges;       // Header: accept-ranges
            s3::base::OptStr expiration;         // Header: x-amz-expiration
            s3::base::OptStr restore;            // Header: x-amz-restore
            ArchiveStatus archiveStatus;         // Header: x-amz-archive-status
            s3::base::OptStr lastModified;       // Header: Last-Modified
            s3::base::OptI64 contentLength;      // Header: Content-Length
            s3::base::OptStr eTag;               // Header: ETag
            s3::base::OptStr checksumCrc32;      // Header: x-amz-checksum-crc32
            s3::base::OptStr checksumCrc32c;     // Header: x-amz-checksum-crc32c
            s3::base::OptStr checksumCrc64nvme;  // Header: x-amz-checksum-crc64nvme
            s3::base::OptStr checksumSha1;       // Header: x-amz-checksum-sha1
            s3::base::OptStr checksumSha256;     // Header: x-amz-checksum-sha256
            ChecksumType checksumType;           // Header: x-amz-checksum-type
            s3::base::OptI64 missingMeta;        // Header: x-amz-missing-meta
            s3::base::OptStr versionId;          // Header: x-amz-version-id
            s3::base::OptStr cacheControl;       // Header: Cache-Control
            s3::base::OptStr contentDisposition; // Header: Content-Disposition
            s3::base::OptStr contentEncoding;    // Header: Content-Encoding
            s3::base::OptStr contentLanguage;    // Header: Content-Language
            s3::base::OptStr contentType;        // Header: Content-Type
            s3::base::OptStr contentRange;
            s3::base::OptStr expires;                  // Header: Expires
            s3::base::OptStr websiteRedirectLocation;  // Header: x-amz-website-redirect-location
            ServerSideEncryption serverSideEncryption; // Header: x-amz-server-side-encryption
            std::map<std::string, std::string> metadata;
            s3::base::OptStr sSECustomerAlgorithm;               // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr sSECustomerKeyMd5;                  // Header: x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr sSEKmsKeyId;                        // Header: x-amz-server-side-encryption-aws-kms-key-id
            s3::base::OptBool sSEBucketKeyEnabled;               // Header: x-amz-server-side-encryption-bucket-key-enabled
            StorageClass storageClass;                           // Header: x-amz-storage-class
            RequestCharged requestCharged;                       // Header: x-amz-request-charged
            ReplicationStatus replicationStatus;                 // Header: x-amz-replication-status
            s3::base::OptI64 partsCount;                         // Header: x-amz-mp-parts-count
            s3::base::OptI64 tagCount;                           // Header: x-amz-tagging-count
            ObjectLockMode objectLockMode;                       // Header: x-amz-object-lock-mode
            s3::base::OptStr objectLockRetainUntilDate;          // Header: x-amz-object-lock-retain-until-date
            ObjectLockLegalHoldStatus objectLockLegalHoldStatus; // Header: x-amz-object-lock-legal-hold
            std::string expiresString;
            std::string requestId;
        };
    } // namespace model
} // namespace s3