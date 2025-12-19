#include "aws_resp.hpp"

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
            errorNode.append_child(pair.first)
                .append_child(pugi::node_pcdata)
                .set_value(pair.second);
        }
        std::stringstream ss;
        doc.save(ss, "    ", pugi::format_indent);
        return ss.str();
    }
} // namespace s3