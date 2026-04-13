#pragma once

#include <map>
#include <string>
#include <vector>

#include "model/CompletedMultipartUpload.hpp"
#include "model/Delete.hpp"
#include "model/Tagging.hpp"
#include "s3_base.hpp"
#include "s3_error.hpp"

namespace s3
{
    namespace req
    {
        struct BucketAndKey
        {
            s3::base::OptStr bucket; // 桶名, 使用前需确定是否编码
            s3::base::OptStr key;    // 对象名, 使用前需确定是否编码
        };
        BucketAndKey parseBucketAndKeyFromUriWithPathStyle(const std::string& uri);

        s3::err::S3ErrorCode parsePutObjectTaggingBodyXml(const std::string& body, s3::model::Tagging& tagging);
        s3::err::S3ErrorCode parseCompleteMultipartUploadBodyXml(const std::string& body, model::CompletedMultipartUpload& uploadParts);
        s3::err::S3ErrorCode parseDeleteObjectsBodyXml(const std::string& body, model::Delete& deleteNode);
    } // namespace req
} // namespace s3