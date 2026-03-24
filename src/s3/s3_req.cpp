#include "s3_req.hpp"

#include <cerrno>
#include <cstdlib>

#include "pugixml.hpp"

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
            pugi::xml_parse_result parseResult = doc.load_string(body.c_str());
            if (!parseResult)
            {
                return s3::err::S3ErrorCode::InvalidRequest;
            }

            pugi::xml_node taggingNode = doc.child("Tagging");
            if (!taggingNode)
            {
                return s3::err::S3ErrorCode::InvalidRequest;
            }

            pugi::xml_node tagSetNode = taggingNode.child("TagSet");
            if (!tagSetNode)
            {
                return s3::err::S3ErrorCode::InvalidTag;
            }

            for (pugi::xml_node tagNode = tagSetNode.child("Tag"); tagNode; tagNode = tagNode.next_sibling("Tag"))
            {
                pugi::xml_node keyNode = tagNode.child("Key");
                pugi::xml_node valueNode = tagNode.child("Value");
                if (!keyNode || !valueNode)
                {
                    return s3::err::S3ErrorCode::InvalidTag;
                }

                const char* keyText = keyNode.child_value();
                const char* valueText = valueNode.child_value();
                if (keyText == nullptr)
                {
                    return s3::err::S3ErrorCode::InvalidTag;
                }

                model::Tag tag;
                tag.key = keyText;
                tag.value = (valueText == nullptr) ? "" : valueText;
                tagging.tagSet.push_back(tag);
            }

            if (tagging.tagSet.empty())
            {
                return s3::err::S3ErrorCode::InvalidTag;
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
            pugi::xml_parse_result parseResult = doc.load_string(body.c_str());
            if (!parseResult)
            {
                return s3::err::S3ErrorCode::InvalidRequest;
            }

            pugi::xml_node root = doc.child("CompleteMultipartUpload");
            if (!root)
            {
                return s3::err::S3ErrorCode::InvalidRequest;
            }

            for (pugi::xml_node partNode = root.child("Part"); partNode; partNode = partNode.next_sibling("Part"))
            {
                pugi::xml_node eTagNode = partNode.child("ETag");
                pugi::xml_node partNumberNode = partNode.child("PartNumber");
                if (!eTagNode || !partNumberNode)
                {
                    return s3::err::S3ErrorCode::InvalidRequest;
                }

                const char* eTagText = eTagNode.child_value();
                const char* partNumberText = partNumberNode.child_value();
                if (eTagText == nullptr || eTagText[0] == '\0' || partNumberText == nullptr || partNumberText[0] == '\0')
                {
                    return s3::err::S3ErrorCode::InvalidRequest;
                }

                char* end = nullptr;
                errno = 0;
                const long long partNumber = std::strtoll(partNumberText, &end, 10);
                if (errno != 0 || end == partNumberText || (end != nullptr && *end != '\0') || partNumber <= 0)
                {
                    return s3::err::S3ErrorCode::InvalidRequest;
                }

                model::CompletedPart part;
                part.eTag = eTagText;
                part.partNumber = partNumber;

                if (pugi::xml_node n = partNode.child("ChecksumCRC32"))
                {
                    part.checksumCRC32 = n.child_value();
                }
                if (pugi::xml_node n = partNode.child("ChecksumCRC32C"))
                {
                    part.checksumCRC32C = n.child_value();
                }
                if (pugi::xml_node n = partNode.child("ChecksumCRC64NVME"))
                {
                    part.checksumCRC64NVME = n.child_value();
                }
                if (pugi::xml_node n = partNode.child("ChecksumSHA1"))
                {
                    part.checksumSHA1 = n.child_value();
                }
                if (pugi::xml_node n = partNode.child("ChecksumSHA256"))
                {
                    part.checksumSHA256 = n.child_value();
                }

                uploadParts.parts.push_back(part);
            }

            return s3::err::S3ErrorCode::Ok;
        }
        s3::err::S3ErrorCode parseDeleteObjectsBodyXml(const std::string& body, model::Delete deleteNode)
        {
            // TODO
            return s3::err::S3ErrorCode::Ok;
        }
    } // namespace req
} // namespace s3