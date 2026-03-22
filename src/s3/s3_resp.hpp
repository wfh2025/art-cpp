#pragma once

#include <string>

#include "s3_model.hpp"

namespace s3
{
    namespace resp
    {
        std::string toXml(const model::CreateMultipartUploadRequest& req, const model::CreateMultipartUploadResult& res);
        std::string toXml(const model::CompleteMultipartUploadRequest& req, const model::CompleteMultipartUploadResult& res);
        std::string toXml(const model::DeleteObjectsRequest& req, const model::DeleteObjectsResult& res);
        std::string toXml(const model::GetObjectTaggingRequest& req, const model::GetObjectTaggingResult& res);
        std::string toXml(const model::ListObjectsRequest& req, const model::ListObjectsResult& res);
        std::string toXml(const model::ListObjectVersionsRequest& req, const model::ListObjectVersionsResult& res);
        std::string toXml(const model::ListPartsRequest& req, const model::ListPartsResult& res);
    } // namespace resp
} // namespace s3
