#include "s3_resp.hpp"

#include <map>
#include <sstream>
#include <string>

#include "pugixml.hpp"
namespace s3
{
    RestfulErrorResponseBodyBuilder RestfulErrorResponseBodyBuilder::create()
    {
        return RestfulErrorResponseBodyBuilder();
    }

    void RestfulErrorResponseBodyBuilder::kv(const std::string& key, const std::string& value)
    {
        m_errMap[key] = value;
    }

    void RestfulErrorResponseBodyBuilder::kvMap(const std::map<std::string, std::string>& m)
    {
        for (const auto& pair : m)
        {
            m_errMap[pair.first] = pair.second;
        }
    }

    std::string RestfulErrorResponseBodyBuilder::toXml()
    {
        pugi::xml_document doc;
        pugi::xml_node declaration = doc.append_child(pugi::node_declaration);
        declaration.append_attribute("version") = "1.0";
        declaration.append_attribute("encoding") = "UTF-8";
        pugi::xml_node errorNode = doc.append_child("Error");

        for (const auto& pair : m_errMap)
        {
            errorNode.append_child(pair.first).append_child(pugi::node_pcdata).set_value(pair.second);
        }
        std::stringstream ss;
        doc.save(ss, "    ", pugi::format_indent);
        return ss.str();
    }

    std::string buildListObjectsResultToXml(const ListObjectsResult& output)
    {
        pugi::xml_document doc;
        pugi::xml_node root = doc.append_child("ListBucketResult");
        root.append_attribute("xmlns") = "http://s3.amazonaws.com/doc/2006-03-01/";

        root.append_child("Name").append_child(pugi::node_pcdata).set_value(output.name.c_str());
        root.append_child("Prefix").append_child(pugi::node_pcdata).set_value(output.prefix.c_str());
        root.append_child("Marker").append_child(pugi::node_pcdata).set_value(output.marker.c_str());
        root.append_child("MaxKeys").append_child(pugi::node_pcdata).set_value(std::to_string(output.maxKeys).c_str());
        root.append_child("Delimiter").append_child(pugi::node_pcdata).set_value(output.delimiter.c_str());
        root.append_child("EncodingType").append_child(pugi::node_pcdata).set_value(output.encodingType.c_str());
        root.append_child("IsTruncated").append_child(pugi::node_pcdata).set_value(output.isTruncated ? "true" : "false");
        root.append_child("NextMarker").append_child(pugi::node_pcdata).set_value(output.nextMarker.c_str());

        for (const auto& content : output.contents)
        {
            auto contentsNode = root.append_child("Contents");
            contentsNode.append_child("Key").append_child(pugi::node_pcdata).set_value(content.key.c_str());
            contentsNode.append_child("LastModified").append_child(pugi::node_pcdata).set_value(content.lastModified.c_str());
            contentsNode.append_child("ETag").append_child(pugi::node_pcdata).set_value(content.eTag.c_str());
            contentsNode.append_child("Size").append_child(pugi::node_pcdata).set_value(std::to_string(content.size).c_str());
            contentsNode.append_child("StorageClass").append_child(pugi::node_pcdata).set_value(content.storageClass.c_str());
            contentsNode.append_child("ChecksumAlgorithm").append_child(pugi::node_pcdata).set_value(content.checksumAlgorithm.c_str());
            auto ownerNode = contentsNode.append_child("Owner");
            ownerNode.append_child("ID").append_child(pugi::node_pcdata).set_value(content.owner.id.c_str());
            ownerNode.append_child("DisplayName").append_child(pugi::node_pcdata).set_value(content.owner.displayName.c_str());

            auto restoreStatusNode = contentsNode.append_child("RestoreStatus");
            restoreStatusNode.append_child("IsRestoreInProgress")
                .append_child(pugi::node_pcdata)
                .set_value(content.restoreStatus.isRestoreInProgress ? "true" : "false");
            restoreStatusNode.append_child("restoreExpiryDate")
                .append_child(pugi::node_pcdata)
                .set_value(content.restoreStatus.restoreExpiryDate.c_str());
        }

        for (const auto& commonPrefix : output.commonPrefixes)
        {
            auto commonPrefixNode = root.append_child("CommonPrefixes");
            commonPrefixNode.append_child("Prefix").append_child(pugi::node_pcdata).set_value(commonPrefix.prefix.c_str());
        }
        std::stringstream ss;
        doc.save(ss, "    ", pugi::format_indent);
        return ss.str();
    }
} // namespace s3