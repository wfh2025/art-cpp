#include "s3_error.hpp"

#include <unordered_map>
namespace s3
{
    namespace
    {
        const std::unordered_map<S3Error, std::string> ErrMsgMap = {
            {S3Error::Success, "Success"},
            {S3Error::AccessDenied, "Access denied."},
        };
    }

    const char* S3ErrorCategory::name() const noexcept
    {
        return "s3";
    }
    std::string S3ErrorCategory::message(int ev) const
    {
        S3Error err = static_cast<S3Error>(ev);
        auto it = ErrMsgMap.find(err);
        if (it != ErrMsgMap.end())
        {
            return it->second;
        }
        return "Unknown, ev: " + std::to_string(ev);
    }
    const S3ErrorCategory& S3ErrorCategory::instance() noexcept
    {
        static S3ErrorCategory instance;
        return instance;
    }

    const std::error_category& s3_error_category() noexcept
    {
        return S3ErrorCategory::instance();
    }
    std::error_code make_error_code(s3::S3Error e) noexcept
    {
        return std::error_code(static_cast<int>(e), s3_error_category());
    }
} // namespace s3