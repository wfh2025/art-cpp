#pragma once
#include "s3/s3_base.hpp"
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
    } // namespace model
} // namespace s3