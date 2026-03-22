#include "s3_resp.hpp"

#include <sstream>
#include <string>

#include "pugixml.hpp"

namespace s3
{
    namespace resp
    {
        std::string toXml(const model::CreateMultipartUploadRequest& req, const model::CreateMultipartUploadResult& res)
        {
            pugi::xml_document doc;

            pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
            decl.append_attribute("version") = "1.0";
            decl.append_attribute("encoding") = "UTF-8";

            pugi::xml_node root = doc.append_child("InitiateMultipartUploadResult");
            root.append_attribute("xmlns") = "http://s3.amazonaws.com/doc/2006-03-01/";

            root.append_child("Bucket").text().set(req.bucket.c_str());
            root.append_child("Key").text().set(req.key.c_str());
            root.append_child("UploadId").text().set(res.uploadId.c_str());

            std::ostringstream os;
            doc.save(os, "  ", pugi::format_default);
            return os.str();
        }
        std::string toXml(const model::CompleteMultipartUploadRequest& req, const model::CompleteMultipartUploadResult& res)
        {
            return "";
        }

        std::string toXml(const model::DeleteObjectsRequest& req, const model::DeleteObjectsResult& res)
        {
            return "";
        }

        std::string toXml(const model::GetObjectTaggingRequest& req, const model::GetObjectTaggingResult& res)
        {
            return "";
        }

        std::string toXml(const model::ListObjectsRequest& req, const model::ListObjectsResult& res)
        {
            return "";
        }

        std::string toXml(const model::ListObjectVersionsRequest& req, const model::ListObjectVersionsResult& res)
        {
            return "";
        }

        std::string toXml(const model::ListPartsRequest& req, const model::ListPartsResult& res)
        {
            return "";
        }

    } // namespace resp
} // namespace s3
