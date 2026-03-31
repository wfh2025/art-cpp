#include "s3_req.hpp"

#include <string>

#include "pugixml.hpp"
#include "s3_utils.hpp"

namespace s3
{
    namespace req
    {
        s3::err::S3ErrorCode parsePutObjectTaggingBodyXml(const std::string& body, s3::model::Tagging& tagging)
        {
            tagging.tagSet.clear();
            if (body.empty())
            {
                return s3::err::S3ErrorCode::IncompleteBody;
            }

            pugi::xml_document doc;
            if (doc.load_buffer(body.data(), body.size()).status != pugi::status_ok)
            {
                return s3::err::S3ErrorCode::InvalidRequest;
            }

            pugi::xml_node taggingNode = doc.child("Tagging");
            if (taggingNode.empty())
            {
                return s3::err::S3ErrorCode::InvalidRequest;
            }

            pugi::xml_node tagSetNode = taggingNode.child("TagSet");
            if (tagSetNode.empty())
            {
                return s3::err::S3ErrorCode::InvalidTagTagging;
            }

            for (pugi::xml_node tagNode = tagSetNode.child("Tag"); !tagNode.empty(); tagNode = tagNode.next_sibling("Tag"))
            {
                pugi::xml_node keyNode = tagNode.child("Key");
                pugi::xml_node valueNode = tagNode.child("Value");
                if (keyNode.empty())
                {
                    return s3::err::S3ErrorCode::InvalidTagTagging;
                }
                if (valueNode.empty())
                {
                    return s3::err::S3ErrorCode::InvalidTagTagging;
                }

                const char* keyText = keyNode.child_value();
                if (s3::utils::isNullOrEmpty(keyText))
                {
                    return s3::err::S3ErrorCode::InvalidTagTagging;
                }

                model::Tag tag;
                tag.key = keyText;
                tag.value = valueNode.child_value();
                tagging.tagSet.push_back(tag);
            }

            if (tagging.tagSet.empty())
            {
                return s3::err::S3ErrorCode::InvalidTagTagging;
            }

            return s3::err::S3ErrorCode::Ok;
        }

        s3::err::S3ErrorCode parseCompleteMultipartUploadBodyXml(const std::string& body, model::CompletedMultipartUpload& uploadParts)
        {
            uploadParts.parts.clear();
            if (body.empty())
            {
                return s3::err::S3ErrorCode::IncompleteBody;
            }

            pugi::xml_document doc;
            if (doc.load_buffer(body.data(), body.size()).status != pugi::status_ok)
            {
                return s3::err::S3ErrorCode::InvalidRequest;
            }

            pugi::xml_node root = doc.child("CompleteMultipartUpload");
            if (root.empty())
            {
                return s3::err::S3ErrorCode::InvalidRequest;
            }

            for (pugi::xml_node partNode = root.child("Part"); !partNode.empty(); partNode = partNode.next_sibling("Part"))
            {
                pugi::xml_node eTagNode = partNode.child("ETag");
                if (eTagNode.empty())
                {
                    return s3::err::S3ErrorCode::InvalidRequest;
                }
                const char* eTagText = eTagNode.child_value();
                if (s3::utils::isNullOrEmpty(eTagText))
                {
                    return s3::err::S3ErrorCode::InvalidRequest;
                }

                pugi::xml_node partNumberNode = partNode.child("PartNumber");
                if (partNumberNode.empty())
                {
                    return s3::err::S3ErrorCode::InvalidRequest;
                }

                const char* partNumberText = partNumberNode.child_value();
                if (s3::utils::isNullOrEmpty(partNumberText))
                {
                    return s3::err::S3ErrorCode::InvalidRequest;
                }

                s3::base::OptI64 partNumber = s3::utils::parseInt64(partNumberText);
                if ((partNumber.has() == false) || ((partNumber.value() <= 0) || (partNumber.value() > 10000)))
                {
                    return s3::err::S3ErrorCode::InvalidRequest;
                }

                model::CompletedPart part;
                part.eTag = eTagText;
                part.partNumber = partNumber.value();

                pugi::xml_node checksumCRC32Node = partNode.child("ChecksumCRC32");
                if (!checksumCRC32Node.empty())
                {
                    part.checksumCRC32 = checksumCRC32Node.child_value();
                }
                pugi::xml_node checksumCRC32CNode = partNode.child("ChecksumCRC32C");
                if (!checksumCRC32CNode.empty())
                {
                    part.checksumCRC32C = checksumCRC32CNode.child_value();
                }
                pugi::xml_node checksumCRC64NVMENode = partNode.child("ChecksumCRC64NVME");
                if (!checksumCRC64NVMENode.empty())
                {
                    part.checksumCRC64NVME = checksumCRC64NVMENode.child_value();
                }
                pugi::xml_node checksumSHA1Node = partNode.child("ChecksumSHA1");
                if (!checksumSHA1Node.empty())
                {
                    part.checksumSHA1 = checksumSHA1Node.child_value();
                }
                pugi::xml_node checksumSHA256Node = partNode.child("ChecksumSHA256");
                if (!checksumSHA256Node.empty())
                {
                    part.checksumSHA256 = checksumSHA256Node.child_value();
                }

                uploadParts.parts.push_back(part);
            }

            if (uploadParts.parts.empty())
            {
                return s3::err::S3ErrorCode::InvalidRequest;
            }

            return s3::err::S3ErrorCode::Ok;
        }

        s3::err::S3ErrorCode parseDeleteObjectsBodyXml(const std::string& body, model::Delete& deleteNode)
        {
            // https://docs.aws.amazon.com/AmazonS3/latest/API/API_DeleteObjects.html
            deleteNode.objects.clear();
            deleteNode.quiet.reset();

            if (body.empty())
            {
                return s3::err::S3ErrorCode::IncompleteBody;
            }

            pugi::xml_document doc;
            if (doc.load_buffer(body.data(), body.size()).status != pugi::status_ok)
            {
                return s3::err::S3ErrorCode::InvalidRequest;
            }

            pugi::xml_node root = doc.child("Delete");
            if (root.empty())
            {
                return s3::err::S3ErrorCode::InvalidRequest;
            }

            pugi::xml_node quietNode = root.child("Quiet");
            if (!quietNode.empty())
            {
                pugi::xml_text quietText = quietNode.text();
                if (quietText.empty())
                {
                    return s3::err::S3ErrorCode::InvalidRequest;
                }
                deleteNode.quiet = quietText.as_bool(false);
            }

            for (pugi::xml_node objectNode = root.child("Object"); !objectNode.empty(); objectNode = objectNode.next_sibling("Object"))
            {
                if (deleteNode.objects.size() >= 1000)
                {
                    return s3::err::S3ErrorCode::InvalidArgument;
                }

                pugi::xml_node keyNode = objectNode.child("Key");
                if (keyNode.empty())
                {
                    return s3::err::S3ErrorCode::InvalidRequest;
                }
                const char* keyText = keyNode.child_value();
                if (s3::utils::isNullOrEmpty(keyText))
                {
                    return s3::err::S3ErrorCode::InvalidRequest;
                }

                model::ObjectIdentifier oid;
                oid.key = keyText;

                pugi::xml_node versionIdNode = objectNode.child("VersionId");
                if (!versionIdNode.empty())
                {
                    oid.versionId = versionIdNode.child_value();
                }

                pugi::xml_node eTagNode = objectNode.child("ETag");
                if (!eTagNode.empty())
                {
                    oid.eTag = eTagNode.child_value();
                }

                pugi::xml_node lastModifiedTimeNode = objectNode.child("LastModifiedTime");
                if (!lastModifiedTimeNode.empty())
                {
                    oid.lastModifiedTime = lastModifiedTimeNode.child_value();
                }

                pugi::xml_node sizeNode = objectNode.child("Size");
                if (!sizeNode.empty())
                {
                    const char* sizeText = sizeNode.child_value();
                    if (s3::utils::isNullOrEmpty(sizeText))
                    {
                        return s3::err::S3ErrorCode::InvalidRequest;
                    }
                    s3::base::OptI64 sizeVal = s3::utils::parseInt64(std::string(sizeText));
                    if (!sizeVal.has())
                    {
                        return s3::err::S3ErrorCode::InvalidRequest;
                    }
                    oid.size = sizeVal.value();
                }

                deleteNode.objects.push_back(oid);
            }

            if (deleteNode.objects.empty())
            {
                return s3::err::S3ErrorCode::InvalidRequest;
            }

            return s3::err::S3ErrorCode::Ok;
        }
    } // namespace req
} // namespace s3