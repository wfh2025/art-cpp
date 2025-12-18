#ifndef ART_S3_DEF_H_INCLUDED
#define ART_S3_DEF_H_INCLUDED
#include <string>
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
{
public:
    HeadObjectRequest() : m_bucket(""), m_key(""), m_versionId(""), m_partNumber(0) {}

private:
    std::string m_bucket;
    std::string m_key;
    std::string m_versionId;
    int m_partNumber;
};

#endif