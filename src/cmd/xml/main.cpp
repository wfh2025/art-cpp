#include <iostream>
#include <string>
#include "pugixml.hpp"

// 创建示例XML文档
std::string create_sample_xml() {
    return R"(
        <books>
            <book id="1">
                <title>The Great Gatsby</title>
                <author>F. Scott Fitzgerald</author>
                <year>1925</year>
                <price>12.99</price>
            </book>
            <book id="2">
                <title>To Kill a Mockingbird</title>
                <author>Harper Lee</author>
                <year>1960</year>
                <price>10.50</price>
            </book>
        </books>
    )";
}

int main() {
    std::string sample_xml = create_sample_xml();
    pugi::xml_document doc;
    doc.load_string(sample_xml.c_str());
    
    return 0;
}