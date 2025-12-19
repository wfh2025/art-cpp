#ifndef ART_S3_S3_DEF_HPP_INCLUDED
#define ART_S3_S3_DEF_HPP_INCLUDED
#include <cstdint>
#include <string>
#include <vector>

namespace s3
{
    enum class HttpCode
    {
        /* https://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml */
        Continue = 100,
        SwitchingProtocols = 101,
        Processing = 102,
        EarlyHints = 103,
        UploadResumptionSupported = 104,
        OK = 200,
        Created = 201,
        Accepted = 202,
        NonAuthoritativeInformation = 203,
        NoContent = 204,
        ResetContent = 205,
        PartialContent = 206,
        MultiStatus = 207,
        AlreadyReported = 208,
        Found = 302,
        Forbidden = 403,
        NotFound = 404,
        MethodNotAllowed = 405,
        RequestTimeout = 408,
        PreconditionFailed = 412,
        ContentTooLarge = 413,
        UriTooLong = 414,
        RangeNotSatisfiable = 416,
        InternalServerError = 500,
        NotImplemented = 501,
        BadGateway = 502,
        ServiceUnavailable = 503,
        GatewayTimeout = 504,
        HttpVersionNotSupported = 505,
        InsufficientStorage = 507,
    };

    class HeadObjectRequest
    {};

    struct ListObjectsResult
    {
        struct Owner
        {
            std::string id;
            std::string displayName;
        };
        struct CommonPrefix
        {
            std::string prefix;
        };
        struct RestoreStatus
        {
            bool isRestoreInProgress;
            std::string restoreExpiryDate;
        };

        struct Content
        {
            int64_t size;
            std::string key;
            std::string eTag;
            std::string lastModified;
            std::string storageClass;
            std::string checksumType;
            std::string checksumAlgorithm;
            RestoreStatus restoreStatus;
            Owner owner;
        };
        std::string name;
        std::string prefix;
        std::string marker;
        int64_t maxKeys;
        std::string nextMarker;
        std::string delimiter;
        std::string encodingType;
        bool isTruncated;
        std::vector<Content> contents;
        std::vector<CommonPrefix> commonPrefixes;
    };
} // namespace s3

#endif