#pragma once

#include <cstdint>
#include <string>

namespace s3
{
    namespace http
    {
        // HTTP 状态码定义，参考：
        // https://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml
        enum class HttpStatusCode : int
        {
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
            ImUsed = 226,
            MultipleChoices = 300,
            MovedPermanently = 301,
            Found = 302,
            SeeOther = 303,
            NotModified = 304,
            UseProxy = 305,
            TemporaryRedirect = 307,
            PermanentRedirect = 308,
            BadRequest = 400,
            Unauthorized = 401,
            PaymentRequired = 402,
            Forbidden = 403,
            NotFound = 404,
            MethodNotAllowed = 405,
            NotAcceptable = 406,
            ProxyAuthenticationRequired = 407,
            RequestTimeout = 408,
            Conflict = 409,
            Gone = 410,
            LengthRequired = 411,
            PreconditionFailed = 412,
            ContentTooLarge = 413,
            UriTooLong = 414,
            UnsupportedMediaType = 415,
            RangeNotSatisfiable = 416,
            ExpectationFailed = 417,
            MisdirectedRequest = 421,
            UnprocessableContent = 422,
            Locked = 423,
            FailedDependency = 424,
            TooEarly = 425,
            UpgradeRequired = 426,
            PreconditionRequired = 428,
            TooManyRequests = 429,
            RequestHeaderFieldsTooLarge = 431,
            UnavailableForLegalReasons = 451,
            InternalServerError = 500,
            NotImplemented = 501,
            BadGateway = 502,
            ServiceUnavailable = 503,
            GatewayTimeout = 504,
            HttpVersionNotSupported = 505,
            VariantAlsoNegotiates = 506,
            InsufficientStorage = 507,
            LoopDetected = 508,
            NotExtended = 510,
            NetworkAuthenticationRequired = 511,
        };

        // HTTP 方法定义，参考：
        // https://www.iana.org/assignments/http-methods/http-methods.xhtml
        enum class HttpMethod : int
        {
            Unknown,           // 不是http实际method,仅表示无效的Method
            Acl,               // ACL
            BaselineControl,   // BASELINE-CONTROL
            Bind,              // BIND
            Checkin,           // CHECKIN
            Checkout,          // CHECKOUT
            Connect,           // CONNECT
            Copy,              // COPY
            Delete,            // DELETE
            Get,               // GET
            Head,              // HEAD
            Label,             // LABEL
            Link,              // LINK
            Lock,              // LOCK
            Merge,             // MERGE
            Mkactivity,        // MKACTIVITY
            Mkcalendar,        // MKCALENDAR
            Mkcol,             // MKCOL
            Mkredirectref,     // MKREDIRECTREF
            Mkworkspace,       // MKWORKSPACE
            Move,              // MOVE
            Options,           // OPTIONS
            Orderpatch,        // ORDERPATCH
            Patch,             // PATCH
            Post,              // POST
            Pri,               // PRI
            Propfind,          // PROPFIND
            Proppatch,         // PROPPATCH
            Put,               // PUT
            Query,             // QUERY
            Rebind,            // REBIND
            Report,            // REPORT
            Search,            // SEARCH
            Trace,             // TRACE
            Unbind,            // UNBIND
            Uncheckout,        // UNCHECKOUT
            Unlink,            // UNLINK
            Unlock,            // UNLOCK
            Update,            // UPDATE
            Updateredirectref, // UPDATEREDIRECTREF
            VersionControl,    // VERSION-CONTROL
        };

        const char* statusText(HttpStatusCode statusCode);
        const char* methodText(HttpMethod method);
        HttpMethod parseMethod(const std::string& s);

    } // namespace http
} // namespace s3
