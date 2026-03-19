#include "s3_error.hpp"

#include <unordered_map>

#include "spdlog/spdlog.h"

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
            if (args.empty())
            {
                return info.messageTemplate == nullptr ? "" : std::string(info.messageTemplate);
            }

            if (info.messageTemplate == nullptr)
            {
                return "";
            }

            if (info.argCount != args.size())
            {
                // TODO: log
                return info.messageTemplate == nullptr ? "" : std::string(info.messageTemplate);
            }

            auto fr = fmt::runtime(info.messageTemplate);

            switch (args.size())
            {
            case 1: {
                return fmt::format(fr, args[0]);
            }
            case 2: {
                return fmt::format(fr, args[0], args[1]);
            }
            case 3: {
                return fmt::format(fr, args[0], args[1], args[2]);
            }
            case 4: {
                return fmt::format(fr, args[0], args[1], args[2], args[3]);
            }
            case 5: {
                return fmt::format(fr, args[0], args[1], args[2], args[3], args[4]);
            }
            case 6: {
                return fmt::format(fr, args[0], args[1], args[2], args[3], args[4], args[5]);
            }
            case 7: {
                return fmt::format(fr, args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
            }
            case 8: {
                return fmt::format(fr, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
            }
            case 9: {
                return fmt::format(fr, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
            }
            case 10: {
                return fmt::format(fr, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9]);
            }
            case 11: {
                return fmt::format(fr, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10]);
            }
            case 12: {
                return fmt::format(fr, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11]);
            }
            case 13: {
                return fmt::format(fr, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11],
                                   args[12]);
            }
            case 14: {
                return fmt::format(fr, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11],
                                   args[12], args[13]);
            }
            case 15: {
                return fmt::format(fr, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11],
                                   args[12], args[13], args[14]);
            }
            case 16: {
                return fmt::format(fr, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11],
                                   args[12], args[13], args[14], args[15]);
            }
            default: {
                return info.messageTemplate;
            }
            }
        }
        std::string formatErrorMessage(const S3ErrorInfo& info)
        {
            return formatErrorMessage(info, std::vector<std::string>{});
        }

    } // namespace err
} // namespace s3