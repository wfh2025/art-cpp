#include "s3_error.hpp"

#include <unordered_map>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/bundled/args.h"

namespace
{
    const std::unordered_map<s3::err::S3ErrorCode, s3::err::S3ErrorInfo> kS3ErrorInfoTable = {
        {
            s3::err::S3ErrorCode::Ok,
            {
                s3::err::S3ErrorCode::Ok,
                "",
                "",
                0,
                s3::http::HttpStatusCode::OK,
            },
        },
        {
            s3::err::S3ErrorCode::Unknown,
            {
                s3::err::S3ErrorCode::Unknown,
                "",
                "",
                0,
                s3::http::HttpStatusCode::InternalServerError,
            },
        },
        {
            s3::err::S3ErrorCode::InternalError,
            {
                s3::err::S3ErrorCode::InternalError,
                "InternalError",
                "An internal error occurred. Try again.",
                0,
                s3::http::HttpStatusCode::InternalServerError,
            },
        },
        {
            s3::err::S3ErrorCode::AccessGrantsQuotaExceededError,
            {
                s3::err::S3ErrorCode::AccessGrantsQuotaExceededError,
                "AccessGrantsQuotaExceededError",
                "The access grants quota has been exceeded. Access Grants Quota: {}. Please reach out to S3 if an increase is required.",
                1,
                s3::http::HttpStatusCode::Conflict,
            },
        },
    };

} // namespace

namespace s3
{
    namespace err
    {
        const s3::err::S3ErrorInfo& getS3ErrorInfo(s3::err::S3ErrorCode s3ErrorCode)
        {
            auto it = kS3ErrorInfoTable.find(s3ErrorCode);
            if (it != kS3ErrorInfoTable.end())
            {
                return it->second;
            }
            return kS3ErrorInfoTable.at(s3::err::S3ErrorCode::Unknown);
        }

        std::string formatErrorMessage(const S3ErrorInfo& info, const std::vector<std::string>& args)
        {
            // caution: messageTemplate不可能为空或空指针，因为在定义不同的S3ErrorInfo的时候就已经确认
            if (info.argCount != args.size())
            {
                SPDLOG_ERROR("Failed to format error message. template: {}, expect args count: {}, actual args count: {}", info.messageTemplate, info.argCount, args.size());
                return info.messageTemplate;
            }

            fmt::dynamic_format_arg_store<fmt::format_context> store;
            for (std::size_t i = 0; i < args.size(); ++i)
            {
                store.push_back(args[i]);
            }

            return fmt::vformat(info.messageTemplate, store);
        }
    } // namespace err
} // namespace s3