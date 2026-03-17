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
            Ok = 0,
            Unknown = 1,
            AccessDenied = 3,
            BadDigest = 10,
            AccessGrantsQuotaExceededError = 11,
            EntityTooSmall = 22,
            EntityTooLarge = 23,
            IncompleteBody = 27,
            InlineDataTooLarge = 30,
            InternalError = 31,
            InvalidAccessKeyId = 32,
            InvalidArgument = 36,
            InvalidBucketName = 38,
            InvalidDigest = 41,
            InvalidEncryptionAlgorithmError = 42,
            InvalidHostHeader = 43,
            InvalidHttpMethod = 44,
            InvalidPart = 47,
            InvalidPartOrder = 48,
            InvalidRange = 51,
            InvalidRegion = 52,
            InvalidRequest = 53,
            InvalidSignature = 55,
            InvalidSecurity = 56,
            InvalidStorageClass = 58,
            InvalidURI = 61,
            KeyTooLongError = 62,
            NoSuchBucket = 82,
            NoSuchKey = 85,
            NoSuchTagSet = 90,
            NoSuchUpload = 91,
            NoSuchVersion = 92,
            NotImplemented = 94,
            NotModified = 95,
            SignatureDoesNotMatch = 114,
            UnsupportedArgument = 128,
            UnsupportedSignature = 129,
            InvalidTag = 133,
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
