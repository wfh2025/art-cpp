#include "s3_http.hpp"

#include <algorithm>
#include <cctype>

namespace s3
{
    namespace http
    {
        const char* methodText(HttpMethod method)
        {
            switch (method)
            {
            case HttpMethod::Acl:
                return "ACL";
            case HttpMethod::BaselineControl:
                return "BASELINE-CONTROL";
            case HttpMethod::Bind:
                return "BIND";
            case HttpMethod::Checkin:
                return "CHECKIN";
            case HttpMethod::Checkout:
                return "CHECKOUT";
            case HttpMethod::Connect:
                return "CONNECT";
            case HttpMethod::Copy:
                return "COPY";
            case HttpMethod::Delete:
                return "DELETE";
            case HttpMethod::Get:
                return "GET";
            case HttpMethod::Head:
                return "HEAD";
            case HttpMethod::Label:
                return "LABEL";
            case HttpMethod::Link:
                return "LINK";
            case HttpMethod::Lock:
                return "LOCK";
            case HttpMethod::Merge:
                return "MERGE";
            case HttpMethod::Mkactivity:
                return "MKACTIVITY";
            case HttpMethod::Mkcalendar:
                return "MKCALENDAR";
            case HttpMethod::Mkcol:
                return "MKCOL";
            case HttpMethod::Mkredirectref:
                return "MKREDIRECTREF";
            case HttpMethod::Mkworkspace:
                return "MKWORKSPACE";
            case HttpMethod::Move:
                return "MOVE";
            case HttpMethod::Options:
                return "OPTIONS";
            case HttpMethod::Orderpatch:
                return "ORDERPATCH";
            case HttpMethod::Patch:
                return "PATCH";
            case HttpMethod::Post:
                return "POST";
            case HttpMethod::Pri:
                return "PRI";
            case HttpMethod::Propfind:
                return "PROPFIND";
            case HttpMethod::Proppatch:
                return "PROPPATCH";
            case HttpMethod::Put:
                return "PUT";
            case HttpMethod::Query:
                return "QUERY";
            case HttpMethod::Rebind:
                return "REBIND";
            case HttpMethod::Report:
                return "REPORT";
            case HttpMethod::Search:
                return "SEARCH";
            case HttpMethod::Trace:
                return "TRACE";
            case HttpMethod::Unbind:
                return "UNBIND";
            case HttpMethod::Uncheckout:
                return "UNCHECKOUT";
            case HttpMethod::Unlink:
                return "UNLINK";
            case HttpMethod::Unlock:
                return "UNLOCK";
            case HttpMethod::Update:
                return "UPDATE";
            case HttpMethod::Updateredirectref:
                return "UPDATEREDIRECTREF";
            case HttpMethod::VersionControl:
                return "VERSION-CONTROL";
            case HttpMethod::Unknown:
            default:
                return "UNKNOWN";
            }
        }

        HttpMethod parseMethod(const std::string& s)
        {
            if (s.empty())
            {
                return HttpMethod::Unknown;
            }
            std::string upper = s;
            std::transform(upper.begin(), upper.end(), upper.begin(), [](unsigned char c) { return static_cast<char>(std::toupper(c)); });

            if (upper == "ACL")
                return HttpMethod::Acl;
            if (upper == "BASELINE-CONTROL")
                return HttpMethod::BaselineControl;
            if (upper == "BIND")
                return HttpMethod::Bind;
            if (upper == "CHECKIN")
                return HttpMethod::Checkin;
            if (upper == "CHECKOUT")
                return HttpMethod::Checkout;
            if (upper == "CONNECT")
                return HttpMethod::Connect;
            if (upper == "COPY")
                return HttpMethod::Copy;
            if (upper == "DELETE")
                return HttpMethod::Delete;
            if (upper == "GET")
                return HttpMethod::Get;
            if (upper == "HEAD")
                return HttpMethod::Head;
            if (upper == "LABEL")
                return HttpMethod::Label;
            if (upper == "LINK")
                return HttpMethod::Link;
            if (upper == "LOCK")
                return HttpMethod::Lock;
            if (upper == "MERGE")
                return HttpMethod::Merge;
            if (upper == "MKACTIVITY")
                return HttpMethod::Mkactivity;
            if (upper == "MKCALENDAR")
                return HttpMethod::Mkcalendar;
            if (upper == "MKCOL")
                return HttpMethod::Mkcol;
            if (upper == "MKREDIRECTREF")
                return HttpMethod::Mkredirectref;
            if (upper == "MKWORKSPACE")
                return HttpMethod::Mkworkspace;
            if (upper == "MOVE")
                return HttpMethod::Move;
            if (upper == "OPTIONS")
                return HttpMethod::Options;
            if (upper == "ORDERPATCH")
                return HttpMethod::Orderpatch;
            if (upper == "PATCH")
                return HttpMethod::Patch;
            if (upper == "POST")
                return HttpMethod::Post;
            if (upper == "PRI")
                return HttpMethod::Pri;
            if (upper == "PROPFIND")
                return HttpMethod::Propfind;
            if (upper == "PROPPATCH")
                return HttpMethod::Proppatch;
            if (upper == "PUT")
                return HttpMethod::Put;
            if (upper == "QUERY")
                return HttpMethod::Query;
            if (upper == "REBIND")
                return HttpMethod::Rebind;
            if (upper == "REPORT")
                return HttpMethod::Report;
            if (upper == "SEARCH")
                return HttpMethod::Search;
            if (upper == "TRACE")
                return HttpMethod::Trace;
            if (upper == "UNBIND")
                return HttpMethod::Unbind;
            if (upper == "UNCHECKOUT")
                return HttpMethod::Uncheckout;
            if (upper == "UNLINK")
                return HttpMethod::Unlink;
            if (upper == "UNLOCK")
                return HttpMethod::Unlock;
            if (upper == "UPDATE")
                return HttpMethod::Update;
            if (upper == "UPDATEREDIRECTREF")
                return HttpMethod::Updateredirectref;
            if (upper == "VERSION-CONTROL")
                return HttpMethod::VersionControl;
            return HttpMethod::Unknown;
        }

        const char* statusText(HttpStatusCode statusCode)
        {
            switch (statusCode)
            {
            case HttpStatusCode::Continue:
                return "Continue";
            case HttpStatusCode::SwitchingProtocols:
                return "Switching Protocols";
            case HttpStatusCode::Processing:
                return "Processing";
            case HttpStatusCode::EarlyHints:
                return "Early Hints";
            case HttpStatusCode::UploadResumptionSupported:
                return "Upload Resumption Supported";

            case HttpStatusCode::OK:
                return "OK";
            case HttpStatusCode::Created:
                return "Created";
            case HttpStatusCode::Accepted:
                return "Accepted";
            case HttpStatusCode::NonAuthoritativeInformation:
                return "Non-Authoritative Information";
            case HttpStatusCode::NoContent:
                return "No Content";
            case HttpStatusCode::ResetContent:
                return "Reset Content";
            case HttpStatusCode::PartialContent:
                return "Partial Content";
            case HttpStatusCode::MultiStatus:
                return "Multi-Status";
            case HttpStatusCode::AlreadyReported:
                return "Already Reported";
            case HttpStatusCode::ImUsed:
                return "IM Used";
            case HttpStatusCode::MultipleChoices:
                return "Multiple Choices";
            case HttpStatusCode::MovedPermanently:
                return "Moved Permanently";
            case HttpStatusCode::Found:
                return "Found";
            case HttpStatusCode::SeeOther:
                return "See Other";
            case HttpStatusCode::NotModified:
                return "Not Modified";
            case HttpStatusCode::UseProxy:
                return "Use Proxy";
            case HttpStatusCode::TemporaryRedirect:
                return "Temporary Redirect";
            case HttpStatusCode::PermanentRedirect:
                return "Permanent Redirect";
            case HttpStatusCode::BadRequest:
                return "Bad Request";
            case HttpStatusCode::Unauthorized:
                return "Unauthorized";
            case HttpStatusCode::PaymentRequired:
                return "Payment Required";
            case HttpStatusCode::Forbidden:
                return "Forbidden";
            case HttpStatusCode::NotFound:
                return "Not Found";
            case HttpStatusCode::MethodNotAllowed:
                return "Method Not Allowed";
            case HttpStatusCode::NotAcceptable:
                return "Not Acceptable";
            case HttpStatusCode::ProxyAuthenticationRequired:
                return "Proxy Authentication Required";
            case HttpStatusCode::RequestTimeout:
                return "Request Timeout";
            case HttpStatusCode::Conflict:
                return "Conflict";
            case HttpStatusCode::Gone:
                return "Gone";
            case HttpStatusCode::LengthRequired:
                return "Length Required";
            case HttpStatusCode::PreconditionFailed:
                return "Precondition Failed";
            case HttpStatusCode::ContentTooLarge:
                return "Content Too Large";
            case HttpStatusCode::UriTooLong:
                return "URI Too Long";
            case HttpStatusCode::UnsupportedMediaType:
                return "Unsupported Media Type";
            case HttpStatusCode::RangeNotSatisfiable:
                return "Range Not Satisfiable";
            case HttpStatusCode::ExpectationFailed:
                return "Expectation Failed";
            case HttpStatusCode::MisdirectedRequest:
                return "Misdirected Request";
            case HttpStatusCode::UnprocessableContent:
                return "Unprocessable Content";
            case HttpStatusCode::Locked:
                return "Locked";
            case HttpStatusCode::FailedDependency:
                return "Failed Dependency";
            case HttpStatusCode::TooEarly:
                return "Too Early";
            case HttpStatusCode::UpgradeRequired:
                return "Upgrade Required";
            case HttpStatusCode::PreconditionRequired:
                return "Precondition Required";
            case HttpStatusCode::TooManyRequests:
                return "Too Many Requests";
            case HttpStatusCode::RequestHeaderFieldsTooLarge:
                return "Request Header Fields Too Large";
            case HttpStatusCode::UnavailableForLegalReasons:
                return "Unavailable For Legal Reasons";

            case HttpStatusCode::InternalServerError:
                return "Internal Server Error";
            case HttpStatusCode::NotImplemented:
                return "Not Implemented";
            case HttpStatusCode::BadGateway:
                return "Bad Gateway";
            case HttpStatusCode::ServiceUnavailable:
                return "Service Unavailable";
            case HttpStatusCode::GatewayTimeout:
                return "Gateway Timeout";
            case HttpStatusCode::HttpVersionNotSupported:
                return "HTTP Version Not Supported";
            case HttpStatusCode::VariantAlsoNegotiates:
                return "Variant Also Negotiates";
            case HttpStatusCode::InsufficientStorage:
                return "Insufficient Storage";
            case HttpStatusCode::LoopDetected:
                return "Loop Detected";
            case HttpStatusCode::NotExtended:
                return "Not Extended";
            case HttpStatusCode::NetworkAuthenticationRequired:
                return "Network Authentication Required";
            default:
                return "Unknown";
            }
        }
    } // namespace http
} // namespace s3
