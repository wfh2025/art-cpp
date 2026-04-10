#pragma once

#include <cstdint>
#include <map>
#include <string>

#include "s3_base.hpp"

namespace s3
{
    namespace auth
    {
        s3::base::OptStr sha256HashHex(const std::string& data);
        s3::base::OptStr hmacSha256Hex(const std::string& key, const std::string& data);
        std::string buildScope(const std::string& accessKeyId, const std::string& date, const std::string& region, const std::string& service);
        std::string buildCredentialScope(const std::string& date, const std::string& region, const std::string& service);
        std::string buildCanonicalRequest(const std::string& httpMethod, const std::string& canonicalUri, const std::string& canonicalQueryString,
                                          const std::string& canonicalHeaders, const std::string& signedHeaders, const std::string& hashedPayload);

        // caution: queryMap均未编码
        std::string buildCanonicalQueryString(const std::map<std::string, std::string>& queryMap);

        // caution: headers是来自http的头，未做任何修改
        std::string buildCanonicalHeaders(const std::map<std::string, std::string>& headers);
    } // namespace auth
} // namespace s3