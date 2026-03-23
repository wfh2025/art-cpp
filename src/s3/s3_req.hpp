#pragma once

#include <map>
#include <string>
#include <vector>

#include "model/CompletedMultipartUpload.hpp"
#include "s3_base.hpp"
#include "s3_error.hpp"

namespace s3
{
    namespace req
    {
        s3::err::S3ErrorCode parsePutObjectTaggingBodyXml(const std::string& body, std::map<std::string, std::string>& tagging);

        s3::err::S3ErrorCode parseCompleteMultipartUploadBodyXml(const std::string& body, model::CompletedMultipartUpload& uploadParts);
    } // namespace req
} // namespace s3