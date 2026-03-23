#include "s3_def.hpp"

#include <algorithm>
#include <cctype>

namespace s3
{
    const char* s3ApiKindToString(S3ApiKind apiKind) noexcept
    {
        switch (apiKind)
        {
        case S3ApiKind::Unknown:
            return "Unknown";
        case S3ApiKind::CreateBucket:
            return "CreateBucket";
        case S3ApiKind::DeleteBucket:
            return "DeleteBucket";
        case S3ApiKind::HeadBucket:
            return "HeadBucket";
        case S3ApiKind::ListBuckets:
            return "ListBuckets";
        case S3ApiKind::ListObjectVersions:
            return "ListObjectVersions";
        case S3ApiKind::ListBucketObjects:
            return "ListBucketObjects";
        case S3ApiKind::GetBucketAcl:
            return "GetBucketAcl";
        case S3ApiKind::PutBucketAcl:
            return "PutBucketAcl";
        case S3ApiKind::DeleteBucketAcl:
            return "DeleteBucketAcl";
        case S3ApiKind::GetBucketPolicy:
            return "GetBucketPolicy";
        case S3ApiKind::PutBucketPolicy:
            return "PutBucketPolicy";
        case S3ApiKind::DeleteBucketPolicy:
            return "DeleteBucketPolicy";
        case S3ApiKind::GetBucketTagging:
            return "GetBucketTagging";
        case S3ApiKind::PutBucketTagging:
            return "PutBucketTagging";
        case S3ApiKind::DeleteBucketTagging:
            return "DeleteBucketTagging";
        case S3ApiKind::ListObjects:
            return "ListObjects";
        case S3ApiKind::ListObjectsV2:
            return "ListObjectsV2";
        case S3ApiKind::PutObject:
            return "PutObject";
        case S3ApiKind::GetObject:
            return "GetObject";
        case S3ApiKind::HeadObject:
            return "HeadObject";
        case S3ApiKind::DeleteObject:
            return "DeleteObject";
        case S3ApiKind::DeleteObjects:
            return "DeleteObjects";
        case S3ApiKind::CopyObject:
            return "CopyObject";
        case S3ApiKind::GetObjectTagging:
            return "GetObjectTagging";
        case S3ApiKind::PutObjectTagging:
            return "PutObjectTagging";
        case S3ApiKind::DeleteObjectTagging:
            return "DeleteObjectTagging";
        case S3ApiKind::CreateMultipartUpload:
            return "CreateMultipartUpload";
        case S3ApiKind::UploadPart:
            return "UploadPart";
        case S3ApiKind::CompleteMultipartUpload:
            return "CompleteMultipartUpload";
        case S3ApiKind::AbortMultipartUpload:
            return "AbortMultipartUpload";
        case S3ApiKind::ListMultipartUploads:
            return "ListMultipartUploads";
        case S3ApiKind::ListParts:
            return "ListParts";
        default:
            return "Unknown";
        }
    }

    S3ApiKind stringToS3ApiKind(const std::string& s) noexcept
    {
        if (s.empty())
        {
            return S3ApiKind::Unknown;
        }

        std::string norm = s;
        std::transform(norm.begin(), norm.end(), norm.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

        if (norm == "createbucket")
            return S3ApiKind::CreateBucket;
        if (norm == "deletebucket")
            return S3ApiKind::DeleteBucket;
        if (norm == "headbucket")
            return S3ApiKind::HeadBucket;
        if (norm == "listbuckets")
            return S3ApiKind::ListBuckets;
        if (norm == "listobjectversions")
            return S3ApiKind::ListObjectVersions;
        if (norm == "listbucketobjects")
            return S3ApiKind::ListBucketObjects;
        if (norm == "getbucketacl")
            return S3ApiKind::GetBucketAcl;
        if (norm == "putbucketacl")
            return S3ApiKind::PutBucketAcl;
        if (norm == "deletebucketacl")
            return S3ApiKind::DeleteBucketAcl;
        if (norm == "getbucketpolicy")
            return S3ApiKind::GetBucketPolicy;
        if (norm == "putbucketpolicy")
            return S3ApiKind::PutBucketPolicy;
        if (norm == "deletebucketpolicy")
            return S3ApiKind::DeleteBucketPolicy;
        if (norm == "getbuckettagging")
            return S3ApiKind::GetBucketTagging;
        if (norm == "putbuckettagging")
            return S3ApiKind::PutBucketTagging;
        if (norm == "deletebuckettagging")
            return S3ApiKind::DeleteBucketTagging;
        if (norm == "listobjects")
            return S3ApiKind::ListObjects;
        if (norm == "listobjectsv2")
            return S3ApiKind::ListObjectsV2;
        if (norm == "putobject")
            return S3ApiKind::PutObject;
        if (norm == "getobject")
            return S3ApiKind::GetObject;
        if (norm == "headobject")
            return S3ApiKind::HeadObject;
        if (norm == "deleteobject")
            return S3ApiKind::DeleteObject;
        if (norm == "deleteobjects")
            return S3ApiKind::DeleteObjects;
        if (norm == "copyobject")
            return S3ApiKind::CopyObject;
        if (norm == "getobjecttagging")
            return S3ApiKind::GetObjectTagging;
        if (norm == "putobjecttagging")
            return S3ApiKind::PutObjectTagging;
        if (norm == "deleteobjecttagging")
            return S3ApiKind::DeleteObjectTagging;
        if (norm == "createmultipartupload")
            return S3ApiKind::CreateMultipartUpload;
        if (norm == "uploadpart")
            return S3ApiKind::UploadPart;
        if (norm == "completemultipartupload")
            return S3ApiKind::CompleteMultipartUpload;
        if (norm == "abortmultipartupload")
            return S3ApiKind::AbortMultipartUpload;
        if (norm == "listmultipartuploads")
            return S3ApiKind::ListMultipartUploads;
        if (norm == "listparts")
            return S3ApiKind::ListParts;
        return S3ApiKind::Unknown;
    }
} // namespace s3
