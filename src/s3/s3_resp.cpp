#include "s3_resp.hpp"

#include <sstream>
#include <string>

#include "pugixml.hpp"

namespace s3
{
    namespace resp
    {
        std::string toXml(const model::CreateMultipartUploadResult& res)
        {
            pugi::xml_document doc;

            pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
            decl.append_attribute("version") = "1.0";
            decl.append_attribute("encoding") = "UTF-8";

            pugi::xml_node root = doc.append_child("InitiateMultipartUploadResult");
            root.append_attribute("xmlns") = "http://s3.amazonaws.com/doc/2006-03-01/";

            root.append_child("Bucket").text().set(res.bucket.c_str());
            root.append_child("Key").text().set(res.key.c_str());
            root.append_child("UploadId").text().set(res.uploadId.c_str());

            std::ostringstream os;
            doc.save(os, "  ", pugi::format_default);
            return os.str();
        }

        std::string toXml(const model::CompleteMultipartUploadResult& res)
        {
            pugi::xml_document doc;

            pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
            decl.append_attribute("version") = "1.0";
            decl.append_attribute("encoding") = "UTF-8";

            pugi::xml_node root = doc.append_child("CompleteMultipartUploadResult");
            root.append_attribute("xmlns") = "http://s3.amazonaws.com/doc/2006-03-01/";

            if (res.location.has())
            {
                root.append_child("Location").text().set(res.location.value().c_str());
            }
            root.append_child("Bucket").text().set(res.bucket.value().c_str());
            root.append_child("Key").text().set(res.key.value().c_str());
            root.append_child("ETag").text().set(res.eTag.value().c_str());

            if (res.checksumCRC32.has())
            {
                root.append_child("ChecksumCRC32").text().set(res.checksumCRC32.value().c_str());
            }
            if (res.checksumCRC32C.has())
            {
                root.append_child("ChecksumCRC32C").text().set(res.checksumCRC32C.value().c_str());
            }
            if (res.checksumCRC64NVME.has())
            {
                root.append_child("ChecksumCRC64NVME").text().set(res.checksumCRC64NVME.value().c_str());
            }
            if (res.checksumSHA1.has())
            {
                root.append_child("ChecksumSHA1").text().set(res.checksumSHA1.value().c_str());
            }
            if (res.checksumSHA256.has())
            {
                root.append_child("ChecksumSHA256").text().set(res.checksumSHA256.value().c_str());
            }

            if (res.checksumType != model::ChecksumType::NotSet)
            {
                const char* checksumType = model::checksumTypeToString(res.checksumType);
                root.append_child("ChecksumType").text().set(checksumType);
            }

            std::ostringstream os;
            doc.save(os, "  ", pugi::format_default);
            return os.str();
        }

        std::string toXml(const model::DeleteObjectsRequest& req, const model::DeleteObjectsResult& res)
        {
            // https://docs.aws.amazon.com/AmazonS3/latest/API/API_DeleteObjects.html — DeleteResult
            pugi::xml_document doc;

            pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
            decl.append_attribute("version") = "1.0";
            decl.append_attribute("encoding") = "UTF-8";

            pugi::xml_node root = doc.append_child("DeleteResult");
            root.append_attribute("xmlns") = "http://s3.amazonaws.com/doc/2006-03-01/";

            const bool quiet = req.delete_.quiet.has() && req.delete_.quiet.value();

            if (!quiet)
            {
                for (const model::DeletedObject& d : res.deleted)
                {
                    pugi::xml_node delNode = root.append_child("Deleted");
                    delNode.append_child("Key").text().set(d.key.c_str());
                    if (!d.versionId.empty())
                    {
                        delNode.append_child("VersionId").text().set(d.versionId.c_str());
                    }
                    if (d.deleteMarker)
                    {
                        delNode.append_child("DeleteMarker").text().set("true");
                        if (!d.deleteMarkerVersionId.empty())
                        {
                            delNode.append_child("DeleteMarkerVersionId").text().set(d.deleteMarkerVersionId.c_str());
                        }
                    }
                }
            }

            for (const model::Error& e : res.errors)
            {
                pugi::xml_node errNode = root.append_child("Error");
                errNode.append_child("Key").text().set(e.key.c_str());
                errNode.append_child("Code").text().set(e.code.c_str());
                errNode.append_child("Message").text().set(e.message.c_str());
                if (!e.versionId.empty())
                {
                    errNode.append_child("VersionId").text().set(e.versionId.c_str());
                }
            }

            std::ostringstream os;
            doc.save(os, "  ", pugi::format_default);
            return os.str();
        }

        std::string toXml(const model::GetObjectTaggingResult& res)
        {
            // https://docs.aws.amazon.com/zh_cn/AmazonS3/latest/API/API_GetObjectTagging.html

            pugi::xml_document doc;

            pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
            decl.append_attribute("version") = "1.0";
            decl.append_attribute("encoding") = "UTF-8";

            pugi::xml_node root = doc.append_child("Tagging");
            root.append_attribute("xmlns") = "http://s3.amazonaws.com/doc/2006-03-01/";

            pugi::xml_node tagSetNode = root.append_child("TagSet");
            for (const model::Tag& tag : res.tagSet)
            {
                pugi::xml_node tagNode = tagSetNode.append_child("Tag");
                tagNode.append_child("Key").text().set(tag.key.c_str());
                tagNode.append_child("Value").text().set(tag.value.c_str());
            }

            std::ostringstream os;
            doc.save(os, "  ", pugi::format_default);
            return os.str();
        }

        std::string toXml(const model::ListObjectsResult& res)
        {
            // https://docs.aws.amazon.com/zh_cn/AmazonS3/latest/API/API_ListObjects.html — ListBucketResult

            pugi::xml_document doc;

            pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
            decl.append_attribute("version") = "1.0";
            decl.append_attribute("encoding") = "UTF-8";

            pugi::xml_node root = doc.append_child("ListBucketResult");
            root.append_attribute("xmlns") = "http://s3.amazonaws.com/doc/2006-03-01/";

            if (res.name.has())
            {
                root.append_child("Name").text().set(res.name.value().c_str());
            }
            if (res.prefix.has())
            {
                root.append_child("Prefix").text().set(res.prefix.value().c_str());
            }
            if (res.marker.has())
            {
                root.append_child("Marker").text().set(res.marker.value().c_str());
            }
            if (res.nextMarker.has())
            {
                root.append_child("NextMarker").text().set(res.nextMarker.value().c_str());
            }
            if (res.maxKeys.has())
            {
                root.append_child("MaxKeys").text().set(std::to_string(res.maxKeys.value()).c_str());
            }
            if (res.delimiter.has())
            {
                root.append_child("Delimiter").text().set(res.delimiter.value().c_str());
            }
            if (res.isTruncated.has())
            {
                root.append_child("IsTruncated").text().set(res.isTruncated.value() ? "true" : "false");
            }
            if (res.encodingType == model::EncodingType::Url)
            {
                root.append_child("EncodingType").text().set("url");
            }

            for (const model::Object& obj : res.contents)
            {
                pugi::xml_node c = root.append_child("Contents");
                if (obj.key.has())
                {
                    c.append_child("Key").text().set(obj.key.value().c_str());
                }
                if (obj.lastModified.has())
                {
                    c.append_child("LastModified").text().set(obj.lastModified.value().c_str());
                }
                if (obj.eTag.has())
                {
                    c.append_child("ETag").text().set(obj.eTag.value().c_str());
                }
                if (obj.size.has())
                {
                    c.append_child("Size").text().set(std::to_string(obj.size.value()).c_str());
                }
                if (obj.storageClass.has())
                {
                    c.append_child("StorageClass").text().set(obj.storageClass.value().c_str());
                }
                if (obj.owner.id.has() || obj.owner.displayName.has())
                {
                    pugi::xml_node o = c.append_child("Owner");
                    if (obj.owner.id.has())
                    {
                        o.append_child("ID").text().set(obj.owner.id.value().c_str());
                    }
                    if (obj.owner.displayName.has())
                    {
                        o.append_child("DisplayName").text().set(obj.owner.displayName.value().c_str());
                    }
                }
                for (const std::string& ca : obj.checksumAlgorithm)
                {
                    c.append_child("ChecksumAlgorithm").text().set(ca.c_str());
                }
                if (obj.checksumType.has())
                {
                    c.append_child("ChecksumType").text().set(obj.checksumType.value().c_str());
                }
                if (obj.restoreStatus.has())
                {
                    c.append_child("RestoreStatus").text().set(obj.restoreStatus.value().c_str());
                }
            }

            for (const model::CommonPrefix& cp : res.commonPrefixes)
            {
                root.append_child("CommonPrefixes").append_child("Prefix").text().set(cp.prefix.c_str());
            }

            std::ostringstream os;
            doc.save(os, "  ", pugi::format_default);
            return os.str();
        }

        std::string toXml(const model::ListObjectVersionsResult& res)
        {
            // https://docs.aws.amazon.com/zh_cn/AmazonS3/latest/API/API_ListObjectVersions.html — ListVersionsResult

            pugi::xml_document doc;

            pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
            decl.append_attribute("version") = "1.0";
            decl.append_attribute("encoding") = "UTF-8";

            pugi::xml_node root = doc.append_child("ListVersionsResult");
            root.append_attribute("xmlns") = "http://s3.amazonaws.com/doc/2006-03-01/";

            if (res.name.has())
            {
                root.append_child("Name").text().set(res.name.value().c_str());
            }
            if (res.prefix.has())
            {
                root.append_child("Prefix").text().set(res.prefix.value().c_str());
            }
            if (res.keyMarker.has())
            {
                root.append_child("KeyMarker").text().set(res.keyMarker.value().c_str());
            }
            if (res.versionIdMarker.has())
            {
                root.append_child("VersionIdMarker").text().set(res.versionIdMarker.value().c_str());
            }
            if (res.nextKeyMarker.has())
            {
                root.append_child("NextKeyMarker").text().set(res.nextKeyMarker.value().c_str());
            }
            if (res.nextVersionIdMarker.has())
            {
                root.append_child("NextVersionIdMarker").text().set(res.nextVersionIdMarker.value().c_str());
            }
            if (res.maxKeys.has())
            {
                root.append_child("MaxKeys").text().set(std::to_string(res.maxKeys.value()).c_str());
            }
            if (res.delimiter.has())
            {
                root.append_child("Delimiter").text().set(res.delimiter.value().c_str());
            }
            if (res.isTruncated.has())
            {
                root.append_child("IsTruncated").text().set(res.isTruncated.value() ? "true" : "false");
            }
            if (res.encodingType == model::EncodingType::Url)
            {
                root.append_child("EncodingType").text().set("url");
            }

            for (const model::ObjectVersion& ver : res.versions)
            {
                pugi::xml_node v = root.append_child("Version");
                if (ver.key.has())
                {
                    v.append_child("Key").text().set(ver.key.value().c_str());
                }
                if (ver.versionId.has())
                {
                    v.append_child("VersionId").text().set(ver.versionId.value().c_str());
                }
                if (ver.isLatest.has())
                {
                    v.append_child("IsLatest").text().set(ver.isLatest.value() ? "true" : "false");
                }
                if (ver.lastModified.has())
                {
                    v.append_child("LastModified").text().set(ver.lastModified.value().c_str());
                }
                if (!ver.eTag.empty())
                {
                    v.append_child("ETag").text().set(ver.eTag.c_str());
                }
                if (ver.size.has())
                {
                    v.append_child("Size").text().set(std::to_string(ver.size.value()).c_str());
                }
                if (ver.storageClass.has())
                {
                    v.append_child("StorageClass").text().set(ver.storageClass.value().c_str());
                }
                if (ver.owner.id.has() || ver.owner.displayName.has())
                {
                    pugi::xml_node o = v.append_child("Owner");
                    if (ver.owner.id.has())
                    {
                        o.append_child("ID").text().set(ver.owner.id.value().c_str());
                    }
                    if (ver.owner.displayName.has())
                    {
                        o.append_child("DisplayName").text().set(ver.owner.displayName.value().c_str());
                    }
                }
                for (const std::string& ca : ver.checksumAlgorithm)
                {
                    v.append_child("ChecksumAlgorithm").text().set(ca.c_str());
                }
                if (ver.checksumType.has())
                {
                    v.append_child("ChecksumType").text().set(ver.checksumType.value().c_str());
                }
                if (ver.restoreStatus.has())
                {
                    v.append_child("RestoreStatus").text().set(ver.restoreStatus.value().c_str());
                }
            }

            for (const model::DeleteMarkerEntry& dm : res.deleteMarkers)
            {
                pugi::xml_node d = root.append_child("DeleteMarker");
                if (dm.key.has())
                {
                    d.append_child("Key").text().set(dm.key.value().c_str());
                }
                if (dm.versionId.has())
                {
                    d.append_child("VersionId").text().set(dm.versionId.value().c_str());
                }
                if (dm.isLatest.has())
                {
                    d.append_child("IsLatest").text().set(dm.isLatest.value() ? "true" : "false");
                }
                if (dm.lastModified.has())
                {
                    d.append_child("LastModified").text().set(dm.lastModified.value().c_str());
                }
                if (dm.owner.id.has() || dm.owner.displayName.has())
                {
                    pugi::xml_node o = d.append_child("Owner");
                    if (dm.owner.id.has())
                    {
                        o.append_child("ID").text().set(dm.owner.id.value().c_str());
                    }
                    if (dm.owner.displayName.has())
                    {
                        o.append_child("DisplayName").text().set(dm.owner.displayName.value().c_str());
                    }
                }
            }

            for (const model::CommonPrefix& cp : res.commonPrefixes)
            {
                root.append_child("CommonPrefixes").append_child("Prefix").text().set(cp.prefix.c_str());
            }

            std::ostringstream os;
            doc.save(os, "  ", pugi::format_default);
            return os.str();
        }

        std::string toXml(const model::ListPartsResult& res)
        {
            // https://docs.aws.amazon.com/zh_cn/AmazonS3/latest/API/API_ListParts.html — ListPartsResult

            pugi::xml_document doc;

            pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
            decl.append_attribute("version") = "1.0";
            decl.append_attribute("encoding") = "UTF-8";

            pugi::xml_node root = doc.append_child("ListPartsResult");
            root.append_attribute("xmlns") = "http://s3.amazonaws.com/doc/2006-03-01/";

            if (res.bucket.has())
            {
                root.append_child("Bucket").text().set(res.bucket.value().c_str());
            }
            if (res.key.has())
            {
                root.append_child("Key").text().set(res.key.value().c_str());
            }
            if (res.uploadId.has())
            {
                root.append_child("UploadId").text().set(res.uploadId.value().c_str());
            }
            if (res.initiator.id.has() || res.initiator.displayName.has())
            {
                pugi::xml_node n = root.append_child("Initiator");
                if (res.initiator.id.has())
                {
                    n.append_child("ID").text().set(res.initiator.id.value().c_str());
                }
                if (res.initiator.displayName.has())
                {
                    n.append_child("DisplayName").text().set(res.initiator.displayName.value().c_str());
                }
            }
            if (res.owner.id.has() || res.owner.displayName.has())
            {
                pugi::xml_node o = root.append_child("Owner");
                if (res.owner.id.has())
                {
                    o.append_child("ID").text().set(res.owner.id.value().c_str());
                }
                if (res.owner.displayName.has())
                {
                    o.append_child("DisplayName").text().set(res.owner.displayName.value().c_str());
                }
            }
            if (res.storageClass != model::StorageClass::NotSet)
            {
                root.append_child("StorageClass").text().set(model::storageClassToString(res.storageClass));
            }
            if (res.partNumberMarker.has())
            {
                root.append_child("PartNumberMarker").text().set(std::to_string(res.partNumberMarker.value()).c_str());
            }
            if (res.nextPartNumberMarker.has())
            {
                root.append_child("NextPartNumberMarker").text().set(std::to_string(res.nextPartNumberMarker.value()).c_str());
            }
            if (res.maxParts.has())
            {
                root.append_child("MaxParts").text().set(std::to_string(res.maxParts.value()).c_str());
            }
            if (res.isTruncated.has())
            {
                root.append_child("IsTruncated").text().set(res.isTruncated.value() ? "true" : "false");
            }

            switch (res.checksumAlgorithm)
            {
            case model::ChecksumAlgorithm::CRC32:
                root.append_child("ChecksumAlgorithm").text().set("CRC32");
                break;
            case model::ChecksumAlgorithm::CRC32C:
                root.append_child("ChecksumAlgorithm").text().set("CRC32C");
                break;
            case model::ChecksumAlgorithm::SHA1:
                root.append_child("ChecksumAlgorithm").text().set("SHA1");
                break;
            case model::ChecksumAlgorithm::SHA256:
                root.append_child("ChecksumAlgorithm").text().set("SHA256");
                break;
            case model::ChecksumAlgorithm::CRC64NVME:
                root.append_child("ChecksumAlgorithm").text().set("CRC64NVME");
                break;
            default:
                break;
            }
            if (res.checksumType != model::ChecksumType::NotSet)
            {
                root.append_child("ChecksumType").text().set(model::checksumTypeToString(res.checksumType));
            }
            if (res.abortDate.has())
            {
                root.append_child("AbortDate").text().set(res.abortDate.value().c_str());
            }
            if (res.abortRuleId.has())
            {
                root.append_child("AbortRuleId").text().set(res.abortRuleId.value().c_str());
            }

            for (const model::Part& p : res.parts)
            {
                pugi::xml_node pn = root.append_child("Part");
                if (p.partNumber.has())
                {
                    pn.append_child("PartNumber").text().set(std::to_string(p.partNumber.value()).c_str());
                }
                if (p.lastModified.has())
                {
                    pn.append_child("LastModified").text().set(p.lastModified.value().c_str());
                }
                if (p.eTag.has())
                {
                    pn.append_child("ETag").text().set(p.eTag.value().c_str());
                }
                if (p.size.has())
                {
                    pn.append_child("Size").text().set(std::to_string(p.size.value()).c_str());
                }
                if (p.checksumCRC32.has())
                {
                    pn.append_child("ChecksumCRC32").text().set(p.checksumCRC32.value().c_str());
                }
                if (p.checksumCRC32C.has())
                {
                    pn.append_child("ChecksumCRC32C").text().set(p.checksumCRC32C.value().c_str());
                }
                if (p.checksumCRC64NVME.has())
                {
                    pn.append_child("ChecksumCRC64NVME").text().set(p.checksumCRC64NVME.value().c_str());
                }
                if (p.checksumSHA1.has())
                {
                    pn.append_child("ChecksumSHA1").text().set(p.checksumSHA1.value().c_str());
                }
                if (p.checksumSHA256.has())
                {
                    pn.append_child("ChecksumSHA256").text().set(p.checksumSHA256.value().c_str());
                }
            }

            std::ostringstream os;
            doc.save(os, "  ", pugi::format_default);
            return os.str();
        }

        std::string toXml(const model::ListMultipartUploadsResult& res)
        {
            // https://docs.aws.amazon.com/zh_cn/AmazonS3/latest/API/API_ListMultipartUploads.html — ListMultipartUploadsResult

            pugi::xml_document doc;

            pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
            decl.append_attribute("version") = "1.0";
            decl.append_attribute("encoding") = "UTF-8";

            pugi::xml_node root = doc.append_child("ListMultipartUploadsResult");
            root.append_attribute("xmlns") = "http://s3.amazonaws.com/doc/2006-03-01/";

            if (res.bucket.has())
            {
                root.append_child("Bucket").text().set(res.bucket.value().c_str());
            }
            if (res.keyMarker.has())
            {
                root.append_child("KeyMarker").text().set(res.keyMarker.value().c_str());
            }
            if (res.uploadIdMarker.has())
            {
                root.append_child("UploadIdMarker").text().set(res.uploadIdMarker.value().c_str());
            }
            if (res.nextKeyMarker.has())
            {
                root.append_child("NextKeyMarker").text().set(res.nextKeyMarker.value().c_str());
            }
            if (res.prefix.has())
            {
                root.append_child("Prefix").text().set(res.prefix.value().c_str());
            }
            if (res.delimiter.has())
            {
                root.append_child("Delimiter").text().set(res.delimiter.value().c_str());
            }
            if (res.nextUploadIdMarker.has())
            {
                root.append_child("NextUploadIdMarker").text().set(res.nextUploadIdMarker.value().c_str());
            }
            if (res.maxUploads.has())
            {
                root.append_child("MaxUploads").text().set(std::to_string(res.maxUploads.value()).c_str());
            }
            if (res.isTruncated.has())
            {
                root.append_child("IsTruncated").text().set(res.isTruncated.value() ? "true" : "false");
            }

            for (const model::MultipartUpload& u : res.uploads)
            {
                pugi::xml_node un = root.append_child("Upload");

                switch (u.checksumAlgorithm)
                {
                case model::ChecksumAlgorithm::CRC32:
                    un.append_child("ChecksumAlgorithm").text().set("CRC32");
                    break;
                case model::ChecksumAlgorithm::CRC32C:
                    un.append_child("ChecksumAlgorithm").text().set("CRC32C");
                    break;
                case model::ChecksumAlgorithm::SHA1:
                    un.append_child("ChecksumAlgorithm").text().set("SHA1");
                    break;
                case model::ChecksumAlgorithm::SHA256:
                    un.append_child("ChecksumAlgorithm").text().set("SHA256");
                    break;
                case model::ChecksumAlgorithm::CRC64NVME:
                    un.append_child("ChecksumAlgorithm").text().set("CRC64NVME");
                    break;
                default:
                    break;
                }
                if (u.checksumType != model::ChecksumType::NotSet)
                {
                    un.append_child("ChecksumType").text().set(model::checksumTypeToString(u.checksumType));
                }
                if (u.initiated.has())
                {
                    un.append_child("Initiated").text().set(u.initiated.value().c_str());
                }
                if (u.initiator.id.has() || u.initiator.displayName.has())
                {
                    pugi::xml_node in = un.append_child("Initiator");
                    if (u.initiator.id.has())
                    {
                        in.append_child("ID").text().set(u.initiator.id.value().c_str());
                    }
                    if (u.initiator.displayName.has())
                    {
                        in.append_child("DisplayName").text().set(u.initiator.displayName.value().c_str());
                    }
                }
                if (u.key.has())
                {
                    un.append_child("Key").text().set(u.key.value().c_str());
                }
                if (u.owner.id.has() || u.owner.displayName.has())
                {
                    pugi::xml_node o = un.append_child("Owner");
                    if (u.owner.id.has())
                    {
                        o.append_child("ID").text().set(u.owner.id.value().c_str());
                    }
                    if (u.owner.displayName.has())
                    {
                        o.append_child("DisplayName").text().set(u.owner.displayName.value().c_str());
                    }
                }
                if (u.storageClass != model::StorageClass::NotSet)
                {
                    un.append_child("StorageClass").text().set(model::storageClassToString(u.storageClass));
                }
                if (u.uploadId.has())
                {
                    un.append_child("UploadId").text().set(u.uploadId.value().c_str());
                }
            }

            for (const model::CommonPrefix& cp : res.commonPrefixes)
            {
                root.append_child("CommonPrefixes").append_child("Prefix").text().set(cp.prefix.c_str());
            }

            if (res.encodingType == model::EncodingType::Url)
            {
                root.append_child("EncodingType").text().set("url");
            }

            std::ostringstream os;
            doc.save(os, "  ", pugi::format_default);
            return os.str();
        }
    } // namespace resp
} // namespace s3
