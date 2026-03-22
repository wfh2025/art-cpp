#pragma once

#include <map>
#include <string>
#include <vector>

#include "model/Delete.hpp"
#include "s3_base.hpp"

namespace s3
{
    namespace model
    {
        struct PutObjectRequest
        {
            std::string bucket;                            // URI: Bucket
            std::string key;                               // URI: Key
            s3::base::OptStr cacheControl;                 // Cache-Control
            s3::base::OptStr contentDisposition;           // Content-Disposition
            s3::base::OptStr contentEncoding;              // Content-Encoding
            s3::base::OptStr contentLanguage;              // Content-Language
            s3::base::OptI64 contentLength;                // Content-Length
            s3::base::OptStr contentMD5;                   // Content-MD5
            s3::base::OptStr contentType;                  // Content-Type
            s3::base::OptStr expires;                      // Expires
            s3::base::OptStr ifMatch;                      // If-Match
            s3::base::OptStr ifNoneMatch;                  // If-None-Match
            s3::base::OptStr amzAcl;                       // x-amz-acl
            s3::base::OptStr amzSdkChecksumAlgorithm;      // x-amz-sdk-checksum-algorithm
            s3::base::OptStr amzChecksumCrc32;             // x-amz-checksum-crc32
            s3::base::OptStr amzChecksumCrc32c;            // x-amz-checksum-crc32c
            s3::base::OptStr amzChecksumCrc64nvme;         // x-amz-checksum-crc64nvme
            s3::base::OptStr amzChecksumSha1;              // x-amz-checksum-sha1
            s3::base::OptStr amzChecksumSha256;            // x-amz-checksum-sha256
            s3::base::OptStr amzExpectedBucketOwner;       // x-amz-expected-bucket-owner
            s3::base::OptStr amzGrantFullControl;          // x-amz-grant-full-control
            s3::base::OptStr amzGrantRead;                 // x-amz-grant-read
            s3::base::OptStr amzGrantReadAcp;              // x-amz-grant-read-acp
            s3::base::OptStr amzGrantWriteAcp;             // x-amz-grant-write-acp
            s3::base::OptStr amzObjectLockLegalHold;       // x-amz-object-lock-legal-hold
            s3::base::OptStr amzObjectLockMode;            // x-amz-object-lock-mode
            s3::base::OptStr amzObjectLockRetainUntilDate; // x-amz-object-lock-retain-until-date
            s3::base::OptStr amzRequestPayer;              // x-amz-request-payer
            s3::base::OptStr amzServerSideEncryption;      // x-amz-server-side-encryption
            s3::base::OptStr amzSseAwsKmsKeyId;            // x-amz-server-side-encryption-aws-kms-key-id
            s3::base::OptBool amzSseBucketKeyEnabled;      // x-amz-server-side-encryption-bucket-key-enabled
            s3::base::OptStr amzSseContext;                // x-amz-server-side-encryption-context
            s3::base::OptStr amzSseCustomerAlgorithm;      // x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKey;            // x-amz-server-side-encryption-customer-key
            s3::base::OptStr amzSseCustomerKeyMd5;         // x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr amzStorageClass;              // x-amz-storage-class
            s3::base::OptStr amzTagging;                   // x-amz-tagging
            s3::base::OptStr amzTrailer;                   // x-amz-trailer
            s3::base::OptStr amzWebsiteRedirectLocation;   // x-amz-website-redirect-location
            s3::base::OptI64 amzWriteOffsetBytes;          // x-amz-write-offset-bytes
        };

        // https://github.com/aws/aws-sdk-cpp/blob/main/generated/src/aws-cpp-sdk-s3/include/aws/s3/model/PutObjectResult.h
        struct PutObjectResult
        {
            s3::base::OptStr amzExpiration;           // x-amz-expiration
            s3::base::OptStr eTag;                    // ETag
            s3::base::OptStr amzChecksumCrc32;        // x-amz-checksum-crc32
            s3::base::OptStr amzChecksumCrc32c;       // x-amz-checksum-crc32c
            s3::base::OptStr amzChecksumCrc64nvme;    // x-amz-checksum-crc64nvme
            s3::base::OptStr amzChecksumSha1;         // x-amz-checksum-sha1
            s3::base::OptStr amzChecksumSha256;       // x-amz-checksum-sha256
            s3::base::OptStr amzChecksumType;         // x-amz-checksum-type
            s3::base::OptStr amzServerSideEncryption; // x-amz-server-side-encryption
            s3::base::OptStr amzVersionId;            // x-amz-version-id
            s3::base::OptStr amzSseCustomerAlgorithm; // x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKeyMd5;    // x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr amzSseAwsKmsKeyId;       // x-amz-server-side-encryption-aws-kms-key-id
            s3::base::OptStr amzSseContext;           // x-amz-server-side-encryption-context
            s3::base::OptBool amzSseBucketKeyEnabled; // x-amz-server-side-encryption-bucket-key-enabled
            s3::base::OptI64 amzObjectSize;           // x-amz-object-size
            s3::base::OptStr amzRequestCharged;       // x-amz-request-charged
        };

        struct GetObjectRequest
        {
            std::string bucket;                          // URI: Bucket
            std::string key;                             // URI: Key
            s3::base::OptI64 partNumber;                 // Query String: partNumber
            s3::base::OptStr responseCacheControl;       // Query String: response-cache-control
            s3::base::OptStr responseContentDisposition; // Query String: response-content-disposition
            s3::base::OptStr responseContentEncoding;    // Query String: response-content-encoding
            s3::base::OptStr responseContentLanguage;    // Query String: response-content-language
            s3::base::OptStr responseContentType;        // Query String: response-content-type
            s3::base::OptStr responseExpires;            // Query String: response-expires
            s3::base::OptStr versionId;                  // Query String: versionId
            s3::base::OptStr ifMatch;                    // Header: If-Match
            s3::base::OptStr ifModifiedSince;            // Header: If-Modified-Since
            s3::base::OptStr ifNoneMatch;                // Header: If-None-Match
            s3::base::OptStr ifUnmodifiedSince;          // Header: If-Unmodified-Since
            s3::base::OptStr range;                      // Header: Range
            s3::base::OptStr amzSseCustomerAlgorithm;    // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKey;          // Header: x-amz-server-side-encryption-customer-key
            s3::base::OptStr amzSseCustomerKeyMd5;       // Header: x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr amzRequestPayer;            // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;     // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzChecksumMode;            // Header: x-amz-checksum-mode
        };

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

        struct AbortMultipartUploadRequest
        {
            std::string bucket;                       // URI: Bucket
            std::string key;                          // URI: Key
            s3::base::OptStr uploadId;                // Query String: uploadId
            s3::base::OptStr amzRequestPayer;         // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;  // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzIfMatchInitiatedTime; // Header: x-amz-if-match-initiated-time
        };

        struct CreateMultipartUploadRequest
        {
            std::string bucket;                            // URI: Bucket
            std::string key;                               // URI: Key
            s3::base::OptStr amzAcl;                       // Header: x-amz-acl
            s3::base::OptStr cacheControl;                 // Header: Cache-Control
            s3::base::OptStr contentDisposition;           // Header: Content-Disposition
            s3::base::OptStr contentEncoding;              // Header: Content-Encoding
            s3::base::OptStr contentLanguage;              // Header: Content-Language
            s3::base::OptStr contentType;                  // Header: Content-Type
            s3::base::OptStr expires;                      // Header: Expires
            s3::base::OptStr amzGrantFullControl;          // Header: x-amz-grant-full-control
            s3::base::OptStr amzGrantRead;                 // Header: x-amz-grant-read
            s3::base::OptStr amzGrantReadAcp;              // Header: x-amz-grant-read-acp
            s3::base::OptStr amzGrantWriteAcp;             // Header: x-amz-grant-write-acp
            s3::base::OptStr amzServerSideEncryption;      // Header: x-amz-server-side-encryption
            s3::base::OptStr amzStorageClass;              // Header: x-amz-storage-class
            s3::base::OptStr amzWebsiteRedirectLocation;   // Header: x-amz-website-redirect-location
            s3::base::OptStr amzSseCustomerAlgorithm;      // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKey;            // Header: x-amz-server-side-encryption-customer-key
            s3::base::OptStr amzSseCustomerKeyMd5;         // Header: x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr amzSseAwsKmsKeyId;            // Header: x-amz-server-side-encryption-aws-kms-key-id
            s3::base::OptStr amzSseContext;                // Header: x-amz-server-side-encryption-context
            s3::base::OptBool amzSseBucketKeyEnabled;      // Header: x-amz-server-side-encryption-bucket-key-enabled
            s3::base::OptStr amzRequestPayer;              // Header: x-amz-request-payer
            s3::base::OptStr amzTagging;                   // Header: x-amz-tagging
            s3::base::OptStr amzObjectLockMode;            // Header: x-amz-object-lock-mode
            s3::base::OptStr amzObjectLockRetainUntilDate; // Header: x-amz-object-lock-retain-until-date
            s3::base::OptStr amzObjectLockLegalHold;       // Header: x-amz-object-lock-legal-hold
            s3::base::OptStr amzExpectedBucketOwner;       // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzChecksumAlgorithm;         // Header: x-amz-checksum-algorithm
            s3::base::OptStr amzChecksumType;              // Header: x-amz-checksum-type
        };

        struct CreateMultipartUploadResult
        {
            s3::base::OptStr amzAbortDate;            // Header: x-amz-abort-date
            s3::base::OptStr amzAbortRuleId;          // Header: x-amz-abort-rule-id
            s3::base::OptStr amzServerSideEncryption; // Header: x-amz-server-side-encryption
            s3::base::OptStr amzSseCustomerAlgorithm; // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKeyMd5;    // Header: x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr amzSseAwsKmsKeyId;       // Header: x-amz-server-side-encryption-aws-kms-key-id
            s3::base::OptStr amzSseContext;           // Header: x-amz-server-side-encryption-context
            s3::base::OptBool amzSseBucketKeyEnabled; // Header: x-amz-server-side-encryption-bucket-key-enabled
            s3::base::OptStr amzRequestCharged;       // Header: x-amz-request-charged
            s3::base::OptStr amzChecksumAlgorithm;    // Header: x-amz-checksum-algorithm
            s3::base::OptStr amzChecksumType;         // Header: x-amz-checksum-type
            std::string uploadId;                     // Body
        };

        struct AbortMultipartUploadResult
        {
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
        };

        struct CompleteMultipartUploadRequest
        {
            std::string bucket;                      // URI: Bucket
            std::string key;                         // URI: Key
            s3::base::OptStr uploadId;               // Query String: uploadId
            s3::base::OptStr ifMatch;                // Header: If-Match
            s3::base::OptStr ifNoneMatch;            // Header: If-None-Match
            s3::base::OptStr amzChecksumCrc32;       // Header: x-amz-checksum-crc32
            s3::base::OptStr amzChecksumCrc32c;      // Header: x-amz-checksum-crc32c
            s3::base::OptStr amzChecksumCrc64nvme;   // Header: x-amz-checksum-crc64nvme
            s3::base::OptStr amzChecksumSha1;        // Header: x-amz-checksum-sha1
            s3::base::OptStr amzChecksumSha256;      // Header: x-amz-checksum-sha256
            s3::base::OptStr amzChecksumType;        // Header: x-amz-checksum-type
            s3::base::OptStr amzMpObjectSize;        // Header: x-amz-mp-object-size
            s3::base::OptStr amzRequestPayer;        // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner; // Header: x-amz-expected-bucket-owner
            std::string body;                        // Body: CompleteMultipartUpload XML
        };

        struct CompleteMultipartUploadResult
        {
            s3::base::OptStr amzExpiration;           // Header: x-amz-expiration
            s3::base::OptStr amzServerSideEncryption; // Header: x-amz-server-side-encryption
            s3::base::OptStr amzVersionId;            // Header: x-amz-version-id
            s3::base::OptStr amzSseAwsKmsKeyId;       // Header: x-amz-server-side-encryption-aws-kms-key-id
            s3::base::OptBool amzSseBucketKeyEnabled; // Header: x-amz-server-side-encryption-bucket-key-enabled
            s3::base::OptStr amzRequestCharged;       // Header: x-amz-request-charged
            s3::base::OptStr location;                // Body
            std::string eTag;                         // Body
            s3::base::OptStr checksumCrc32;           // Body
            s3::base::OptStr checksumCrc32c;          // Body
            s3::base::OptStr checksumCrc64nvme;       // Body
            s3::base::OptStr checksumSha1;            // Body
            s3::base::OptStr checksumSha256;          // Body
            s3::base::OptStr checksumType;            // Body
        };

        struct DeleteObjectRequest
        {
            std::string bucket;                             // URI: Bucket
            std::string key;                                // URI: Key
            s3::base::OptStr versionId;                     // Query String: versionId
            s3::base::OptStr mfa;                           // Header: x-amz-mfa
            s3::base::OptBool amzBypassGovernanceRetention; // Header: x-amz-bypass-governance-retention
            s3::base::OptStr amzRequestPayer;               // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;        // Header: x-amz-expected-bucket-owner
            s3::base::OptStr ifMatch;                       // Header: If-Match
            s3::base::OptStr amzIfMatchLastModifiedTime;    // Header: x-amz-if-match-last-modified-time
            s3::base::OptStr amzIfMatchSize;                // Header: x-amz-if-match-size
        };

        struct DeleteObjectResult
        {
            s3::base::OptBool amzDeleteMarker;  // Header: x-amz-delete-marker
            s3::base::OptStr amzVersionId;      // Header: x-amz-version-id
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
        };

        struct DeleteObjectsRequest
        {
            std::string bucket;                             // URI: Bucket
            s3::base::OptStr contentMD5;                    // Header: Content-MD5
            s3::base::OptStr amzChecksumAlgorithm;          // Header: x-amz-checksum-algorithm
            s3::base::OptStr amzSdkChecksumAlgorithm;       // Header: x-amz-sdk-checksum-algorithm
            s3::base::OptStr mfa;                           // Header: x-amz-mfa
            s3::base::OptBool amzBypassGovernanceRetention; // Header: x-amz-bypass-governance-retention
            s3::base::OptStr amzRequestPayer;               // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;        // Header: x-amz-expected-bucket-owner
            Delete deleteNode;                              // Body: Delete XML node
        };

        struct DeleteObjectsResult
        {
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
            std::string body;                   // Body: DeleteResult XML
        };

        struct DeleteObjectTaggingRequest
        {
            std::string bucket;                      // URI: Bucket
            std::string key;                         // URI: Key
            s3::base::OptStr versionId;              // Query String: versionId
            s3::base::OptStr amzExpectedBucketOwner; // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzRequestPayer;        // Header: x-amz-request-payer
        };

        struct DeleteObjectTaggingResult
        {
            s3::base::OptStr amzVersionId; // Header: x-amz-version-id
        };

        struct GetObjectTaggingRequest
        {
            std::string bucket;                      // URI: Bucket
            std::string key;                         // URI: Key
            s3::base::OptStr versionId;              // Query String: versionId
            s3::base::OptStr amzExpectedBucketOwner; // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzRequestPayer;        // Header: x-amz-request-payer
        };

        struct GetObjectTaggingResult
        {
            s3::base::OptStr amzVersionId;              // Header: x-amz-version-id
            s3::base::OptStr amzRequestCharged;         // Header: x-amz-request-charged
            std::map<std::string, std::string> tagging; // Body: Tagging XML
        };

        struct HeadObjectRequest
        {
            std::string bucket;                       // URI: Bucket
            std::string key;                          // URI: Key
            s3::base::OptStr ifMatch;                 // Header: If-Match
            s3::base::OptStr ifModifiedSince;         // Header: If-Modified-Since
            s3::base::OptStr ifNoneMatch;             // Header: If-None-Match
            s3::base::OptStr ifUnmodifiedSince;       // Header: If-Unmodified-Since
            s3::base::OptStr range;                   // Header: Range
            s3::base::OptStr versionId;               // Query String: versionId
            s3::base::OptI64 partNumber;              // Query String: partNumber
            s3::base::OptStr amzSseCustomerAlgorithm; // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKey;       // Header: x-amz-server-side-encryption-customer-key
            s3::base::OptStr amzSseCustomerKeyMd5;    // Header: x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr amzRequestPayer;         // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;  // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzChecksumMode;         // Header: x-amz-checksum-mode
        };

        struct HeadObjectResult
        {
            s3::base::OptBool amzDeleteMarker;             // Header: x-amz-delete-marker
            s3::base::OptStr acceptRanges;                 // Header: accept-ranges
            s3::base::OptStr amzExpiration;                // Header: x-amz-expiration
            s3::base::OptStr amzRestore;                   // Header: x-amz-restore
            s3::base::OptStr amzArchiveStatus;             // Header: x-amz-archive-status
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

        struct ListObjectsRequest
        {
            std::string bucket;                      // URI: Bucket
            s3::base::OptStr delimiter;              // Query String: delimiter
            s3::base::OptStr encodingType;           // Query String: encoding-type
            s3::base::OptStr marker;                 // Query String: marker
            s3::base::OptI64 maxKeys;                // Query String: max-keys
            s3::base::OptStr prefix;                 // Query String: prefix
            s3::base::OptStr amzRequestPayer;        // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner; // Header: x-amz-expected-bucket-owner
        };

        struct Owner
        {
            s3::base::OptStr id;
            s3::base::OptStr displayName;
        };

        struct CommonPrefix
        {
            std::string prefix;
        };

        struct Object
        {
            s3::base::OptStr key;
            s3::base::OptStr lastModified;
            s3::base::OptStr eTag;
            std::vector<std::string> checksumAlgorithm;
            s3::base::OptStr checksumType;
            s3::base::OptI64 size;
            s3::base::OptStr storageClass;
            Owner owner;
            s3::base::OptStr restoreStatus;
        };

        struct ListObjectsResult
        {
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
            s3::base::OptBool isTruncated;      // Body: isTruncated
            s3::base::OptStr marker;            // Body: isTruncated
            s3::base::OptStr nextMarker;        // Body: nextMarker
            std::vector<Object> contents;       // Body: contents
            s3::base::OptStr name;
            s3::base::OptStr prefix;
            s3::base::OptStr delimiter;
            s3::base::OptI64 maxKeys;
            std::vector<CommonPrefix> commonPrefixes;
            s3::base::OptStr encodingType;
        };

        struct ListObjectsV2Request
        {
            std::string bucket;                           // URI: Bucket
            s3::base::OptStr listType;                    // Query String: list-type
            s3::base::OptStr continuationToken;           // Query String: continuation-token
            s3::base::OptStr delimiter;                   // Query String: delimiter
            s3::base::OptStr encodingType;                // Query String: encoding-type
            s3::base::OptBool fetchOwner;                 // Query String: fetch-owner
            s3::base::OptI64 maxKeys;                     // Query String: max-keys
            s3::base::OptStr prefix;                      // Query String: prefix
            s3::base::OptStr startAfter;                  // Query String: start-after
            s3::base::OptStr amzRequestPayer;             // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;      // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzOptionalObjectAttributes; // Header: x-amz-optional-object-attributes
        };

        struct ListObjectsV2Result
        {
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
            std::string body;                   // Body: ListBucketResult XML
        };

        struct ListObjectVersionsRequest
        {
            std::string bucket;                      // URI: Bucket
            s3::base::OptStr delimiter;              // Query String: delimiter
            s3::base::OptStr encodingType;           // Query String: encoding-type
            s3::base::OptStr keyMarker;              // Query String: key-marker
            s3::base::OptI64 maxKeys;                // Query String: max-keys
            s3::base::OptStr prefix;                 // Query String: prefix
            s3::base::OptStr versionIdMarker;        // Query String: version-id-marker
            s3::base::OptStr amzRequestPayer;        // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner; // Header: x-amz-expected-bucket-owner
        };

        struct ObjectVersion
        {
            std::string eTag;
            std::vector<std::string> checksumAlgorithm;
            s3::base::OptStr checksumType;
            s3::base::OptI64 size;
            s3::base::OptStr storageClass;
            s3::base::OptStr key;
            s3::base::OptStr versionId;
            s3::base::OptBool isLatest;
            s3::base::OptStr lastModified;
            Owner owner;
            s3::base::OptStr restoreStatus;
        };

        struct DeleteMarkerEntry
        {
            Owner owner;
            s3::base::OptStr key;
            s3::base::OptStr versionId;
            s3::base::OptBool isLatest;
            s3::base::OptStr lastModified;
        };

        struct ListObjectVersionsResult
        {
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
            s3::base::OptBool isTruncated;      // Body
            s3::base::OptStr keyMarker;         // Body
            s3::base::OptStr versionIdMarker;
            s3::base::OptStr nextKeyMarker;
            s3::base::OptStr nextVersionIdMarker;
            std::vector<ObjectVersion> versions;
            std::vector<DeleteMarkerEntry> deleteMarkers;
            s3::base::OptStr name;
            s3::base::OptStr prefix;
            s3::base::OptStr delimiter;
            s3::base::OptI64 maxKeys;
            std::vector<CommonPrefix> commonPrefixes;
            s3::base::OptStr encodingType;
        };

        struct ListPartsRequest
        {
            std::string bucket;                       // URI: Bucket
            std::string key;                          // URI: Key
            s3::base::OptI64 maxParts;                // Query String: max-parts
            s3::base::OptI64 partNumberMarker;        // Query String: part-number-marker
            std::string uploadId;                     // Query String: uploadId
            s3::base::OptStr amzRequestPayer;         // Header: x-amz-request-payer
            s3::base::OptStr amzExpectedBucketOwner;  // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzSseCustomerAlgorithm; // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKey;       // Header: x-amz-server-side-encryption-customer-key
            s3::base::OptStr amzSseCustomerKeyMd5;    // Header: x-amz-server-side-encryption-customer-key-MD5
        };

        struct ListPartsResult
        {
            s3::base::OptStr amzAbortDate;      // Header: x-amz-abort-date
            s3::base::OptStr amzAbortRuleId;    // Header: x-amz-abort-rule-id
            s3::base::OptStr amzRequestCharged; // Header: x-amz-request-charged
            std::string body;                   // Body: ListPartsResult XML
        };

        struct PutObjectTaggingRequest
        {
            std::string bucket;                       // URI: Bucket
            std::string key;                          // URI: Key
            s3::base::OptStr versionId;               // Query String: versionId
            s3::base::OptStr contentMD5;              // Header: Content-MD5
            s3::base::OptStr amzChecksumAlgorithm;    // Header: x-amz-checksum-algorithm
            s3::base::OptStr amzSdkChecksumAlgorithm; // Header: x-amz-sdk-checksum-algorithm
            s3::base::OptStr amzExpectedBucketOwner;  // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzRequestPayer;         // Header: x-amz-request-payer
            std::string body;                         // Body: Tagging XML
        };

        struct PutObjectTaggingResult
        {
            s3::base::OptStr amzVersionId; // Header: x-amz-version-id
        };

        struct UploadPartRequest
        {
            std::string bucket;                       // URI: Bucket
            std::string key;                          // URI: Key
            int64_t partNumber;                       // Query String: partNumber
            std::string uploadId;                     // Query String: uploadId
            s3::base::OptI64 contentLength;           // Header: Content-Length
            s3::base::OptStr contentMD5;              // Header: Content-MD5
            s3::base::OptStr amzSdkChecksumAlgorithm; // Header: x-amz-sdk-checksum-algorithm
            s3::base::OptStr amzChecksumCrc32;        // Header: x-amz-checksum-crc32
            s3::base::OptStr amzChecksumCrc32c;       // Header: x-amz-checksum-crc32c
            s3::base::OptStr amzChecksumCrc64nvme;    // Header: x-amz-checksum-crc64nvme
            s3::base::OptStr amzChecksumSha1;         // Header: x-amz-checksum-sha1
            s3::base::OptStr amzChecksumSha256;       // Header: x-amz-checksum-sha256
            s3::base::OptStr amzExpectedBucketOwner;  // Header: x-amz-expected-bucket-owner
            s3::base::OptStr amzRequestPayer;         // Header: x-amz-request-payer
            s3::base::OptStr amzSseCustomerAlgorithm; // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKey;       // Header: x-amz-server-side-encryption-customer-key
            s3::base::OptStr amzSseCustomerKeyMd5;    // Header: x-amz-server-side-encryption-customer-key-MD5
            std::string body;                         // Body: Part data (binary payload)
        };

        struct UploadPartResult
        {
            s3::base::OptStr amzServerSideEncryption; // Header: x-amz-server-side-encryption
            std::string eTag;                         // Header: ETag
            s3::base::OptStr amzChecksumCrc32;        // Header: x-amz-checksum-crc32
            s3::base::OptStr amzChecksumCrc32c;       // Header: x-amz-checksum-crc32c
            s3::base::OptStr amzChecksumCrc64nvme;    // Header: x-amz-checksum-crc64nvme
            s3::base::OptStr amzChecksumSha1;         // Header: x-amz-checksum-sha1
            s3::base::OptStr amzChecksumSha256;       // Header: x-amz-checksum-sha256
            s3::base::OptStr amzSseCustomerAlgorithm; // Header: x-amz-server-side-encryption-customer-algorithm
            s3::base::OptStr amzSseCustomerKeyMd5;    // Header: x-amz-server-side-encryption-customer-key-MD5
            s3::base::OptStr amzSseAwsKmsKeyId;       // Header: x-amz-server-side-encryption-aws-kms-key-id
            s3::base::OptStr amzRequestCharged;       // Header: x-amz-request-charged
        };
    } // namespace model
} // namespace s3