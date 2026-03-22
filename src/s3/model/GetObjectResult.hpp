#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
        struct GetObjectResult
        {
            s3::base::OptBool amzDeleteMarker;             // Header: x-amz-delete-marker
            s3::base::OptStr acceptRanges;                 // Header: accept-ranges
            s3::base::OptStr amzExpiration;                // Header: x-amz-expiration
            s3::base::OptStr amzRestore;                   // Header: x-amz-restore
            s3::base::OptStr lastModified;                 // Header: Last-Modified
            s3::base::OptI64 contentLength;                // Header: Content-Length
            s3::base::OptStr eTag;                         // Header: ETag
            s3::base::OptStr amzChecksumCrc32;             // Header: x-amz-checksum-crc32
            s3::base::OptStr amzChecksumCrc32c;            // Header: x-amz-checksum-crc32c
            s3::base::OptStr amzChecksumCrc64nvme;         // Header: x-amz-checksum-crc64nvme
            s3::base::OptStr amzChecksumSha1;              // Header: x-amz-checksum-sha1
            s3::base::OptStr amzChecksumSha256;            // Header: x-amz-checksum-sha256
            s3::base::OptStr amzChecksumType;              // Header: x-amz-checksum-type
            s3::base::OptI64 amzMissingMeta;               // Header: x-amz-missing-meta
            s3::base::OptStr amzVersionId;                 // Header: x-amz-version-id
            s3::base::OptStr cacheControl;                 // Header: Cache-Control
            s3::base::OptStr contentDisposition;           // Header: Content-Disposition
            s3::base::OptStr contentEncoding;              // Header: Content-Encoding
            s3::base::OptStr contentLanguage;              // Header: Content-Language
            s3::base::OptStr contentRange;                 // Header: Content-Range
            s3::base::OptStr contentType;                  // Header: Content-Type
            s3::base::OptStr expires;                      // Header: Expires
            s3::base::OptStr amzWebsiteRedirectLocation;   // Header: x-amz-website-redirect-location
            s3::base::OptStr amzServerSideEncryption;      // Header: x-amz-server-side-encryption
            s3::base::OptStr amzSseCustomerAlgorithm;      // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKeyMd5;         // Header: x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr amzSseAwsKmsKeyId;            // Header: x-amz-server-side-encryption-aws-kms-key-id
            s3::base::OptBool amzSseBucketKeyEnabled;      // Header: x-amz-server-side-encryption-bucket-key-enabled
            s3::base::OptStr amzStorageClass;              // Header: x-amz-storage-class
            s3::base::OptStr amzRequestCharged;            // Header: x-amz-request-charged
            s3::base::OptStr amzReplicationStatus;         // Header: x-amz-replication-status
            s3::base::OptI64 amzMpPartsCount;              // Header: x-amz-mp-parts-count
            s3::base::OptI64 amzTaggingCount;              // Header: x-amz-tagging-count
            s3::base::OptStr amzObjectLockMode;            // Header: x-amz-object-lock-mode
            s3::base::OptStr amzObjectLockRetainUntilDate; // Header: x-amz-object-lock-retain-until-date
            s3::base::OptStr amzObjectLockLegalHold;       // Header: x-amz-object-lock-legal-hold
        };
    } // namespace model
} // namespace s3