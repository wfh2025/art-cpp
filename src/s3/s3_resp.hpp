#pragma once

#include <string>

#include "s3_model.hpp"

namespace s3
{
    namespace resp
    {
        std::string toXml(const model::CreateMultipartUploadResult& res);
        std::string toXml(const model::CompleteMultipartUploadResult& res);
        std::string toXml(const model::DeleteObjectsRequest& req, const model::DeleteObjectsResult& res);
        std::string toXml(const model::GetObjectTaggingResult& res);
        std::string toXml(const model::ListObjectsResult& res);
        std::string toXml(const model::ListObjectVersionsResult& res);
        std::string toXml(const model::ListPartsResult& res);
        std::string toXml(const model::ListMultipartUploadsResult& res);
    } // namespace resp
} // namespace s3
