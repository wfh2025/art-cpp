#pragma once

#include <cstdint>
#include <string>

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

    namespace api
    {
        const char* text(S3ApiKind apiKind) noexcept;
        S3ApiKind parse(const std::string& s) noexcept;
    } // namespace api
} // namespace s3
