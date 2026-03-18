#pragma once

#include <string>
#include <vector>

#include "s3_http.hpp"
namespace s3
{
    namespace err
    {
        // https://docs.aws.amazon.com/AmazonS3/latest/API/ErrorResponses.html
        enum class S3ErrorCode
        {
            Ok,
            Unknown,
            AccessDenied,
            BadDigest,
            AccessGrantsQuotaExceededError,
            EntityTooSmall,
            EntityTooLarge,
            IncompleteBody,
            InlineDataTooLarge,
            InternalError,
            InvalidAccessKeyId,
            InvalidArgument,
            InvalidBucketName,
            InvalidDigest,
            InvalidEncryptionAlgorithmError,
            InvalidHostHeader,
            InvalidHttpMethod,
            InvalidPart,
            InvalidPartOrder,
            InvalidRange,
            InvalidRegion,
            InvalidRequest,
            InvalidSignature,
            InvalidSecurity,
            InvalidStorageClass,
            InvalidURI,
            KeyTooLongError,
            NoSuchBucket,
            NoSuchKey,
            NoSuchTagSet,
            NoSuchUpload,
            NoSuchVersion,
            NotImplemented,
            NotModified,
            SignatureDoesNotMatch,
            UnsupportedArgument,
            UnsupportedSignature,
            InvalidTag,
        };

        struct S3ErrorInfo
        {
            S3ErrorCode s3ErrorCode;
            const char* errorName;
            const char* messageTemplate;
            int32_t argCount;
            http::HttpStatusCode httpStatusCode;
        };

        const s3::err::S3ErrorInfo& getS3ErrorInfo(s3::err::S3ErrorCode s3ErrorCode);
        std::string formatErrorMessage(const S3ErrorInfo& info, const std::vector<std::string>& args);
        std::string formatErrorMessage(const S3ErrorInfo& info);

    } // namespace err
} // namespace s3
