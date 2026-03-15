#pragma once

#include <string>

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
            s3::base::OptI64 contentLength{0};
            s3::base::OptStr contentMD5;
            // ChecksumAlgorithm m_checksumAlgorithm{ChecksumAlgorithm::NOT_SET};
            s3::base::OptStr checksumCRC32;
            s3::base::OptStr checksumCRC32C;
            s3::base::OptStr checksumCRC64NVME;
            s3::base::OptStr checksumSHA1;
            s3::base::OptStr checksumSHA256;
            // Aws::Utils::DateTime m_expires{};
            s3::base::OptStr ifMatch;
            s3::base::OptStr ifNoneMatch;
            s3::base::OptStr grantFullControl;
            s3::base::OptStr grantRead;
            s3::base::OptStr grantReadACP;
            s3::base::OptStr grantWriteACP;
            s3::base::OptStr key;
            int64_t writeOffsetBytes{0};
            // Aws::Map<Aws::String, Aws::String> m_metadata;
            // ServerSideEncryption m_serverSideEncryption{ServerSideEncryption::NOT_SET};
            // StorageClass m_storageClass{StorageClass::NOT_SET};
            s3::base::OptStr websiteRedirectLocation;
            s3::base::OptStr sSECustomerAlgorithm;
            s3::base::OptStr sSECustomerKey;
            s3::base::OptStr sSECustomerKeyMD5;
            s3::base::OptStr sSEKMSKeyId;
            s3::base::OptStr sSEKMSEncryptionContext;
            bool m_bucketKeyEnabled{false};
            // RequestPayer m_requestPayer{RequestPayer::NOT_SET};
            s3::base::OptStr tagging;
            // ObjectLockMode m_objectLockMode{ObjectLockMode::NOT_SET};
            // Aws::Utils::DateTime m_objectLockRetainUntilDate{};
            // ObjectLockLegalHoldStatus m_objectLockLegalHoldStatus{ObjectLockLegalHoldStatus::NOT_SET};
            s3::base::OptStr expectedBucketOwner;
            // Aws::Map<Aws::String, Aws::String> m_customizedAccessLogTag;
        };

        // https://github.com/aws/aws-sdk-cpp/blob/main/generated/src/aws-cpp-sdk-s3/include/aws/s3/model/PutObjectResult.h
        struct PutObjectResult
        {};
    } // namespace model
} // namespace s3