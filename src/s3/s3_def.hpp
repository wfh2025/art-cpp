#pragma once

#include <cstdint>
#include <string>

#define S3_OPENSSL_USE_C_API // openssl API: C

namespace s3
{
    enum class S3ApiKind : int32_t
    {
        Unknown,
        CreateBucket,
        DeleteBucket,
        HeadBucket,
        ListBuckets,
        ListObjectVersions,
        ListBucketObjects,
        GetBucketAcl,
        PutBucketAcl,
        DeleteBucketAcl,
        GetBucketPolicy,
        PutBucketPolicy,
        DeleteBucketPolicy,
        GetBucketTagging,
        PutBucketTagging,
        DeleteBucketTagging,
        ListObjects,
        ListObjectsV2,
        PutObject,
        GetObject,
        HeadObject,
        DeleteObject,
        DeleteObjects,
        CopyObject,
        GetObjectTagging,
        PutObjectTagging,
        DeleteObjectTagging,
        CreateMultipartUpload,
        UploadPart,
        CompleteMultipartUpload,
        AbortMultipartUpload,
        ListMultipartUploads,
        ListParts,
    };

    const char* s3ApiKindToString(S3ApiKind apiKind) noexcept;
    S3ApiKind stringToS3ApiKind(const std::string& s) noexcept;
} // namespace s3
