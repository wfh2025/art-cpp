#pragma once
#include <string>

#include "s3/s3_base.hpp"
namespace s3
{
    namespace model
    {
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
    } // namespace model
} // namespace s3