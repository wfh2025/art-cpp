#include "nlohmann/json.hpp"
#include "pugixml.hpp"
#include "ut_config.h"
#include "gtest/gtest.h"
#include <iostream>
#include <sstream>

#ifdef RUN_ALL_TEST_CASE
TEST(nlohmann_json, 001)
{
    nlohmann::json j;

    j["pi"] = 3.141;
    j["happy"] = true;
    j["name"] = "Niels";
    j["nothing"] = nullptr;
    j["answer"]["everything"] = 42;
    j["list"] = {1, 0, 2};
    j["object"] = {
        {"currency", "USD"},
        {"value", 42.99},
    };
    std::string output = j.dump(0);
    EXPECT_TRUE(output.size() > 0);
}

TEST(pugixml, 001)
{
    pugi::xml_document doc;
    pugi::xml_node declaration = doc.prepend_child(pugi::node_declaration);
    declaration.append_attribute("version") = "1.0";
    declaration.append_attribute("encoding") = "UTF-8";
    pugi::xml_node root = doc.append_child("Books");

    // C++
    pugi::xml_node cppBook = root.append_child("Book");
    cppBook.append_attribute("id") = "1";
    cppBook.append_attribute("category") = "编程";
    cppBook.append_child("Title").text().set("C++");

    // Java
    pugi::xml_node javaBook = root.append_child("Book");
    javaBook.append_attribute("id") = "2";
    javaBook.append_attribute("category") = "代码";
    javaBook.append_child("Title").text().set("Java");
    javaBook.append_child("Description")
        .append_child(pugi::node_pcdata)
        .set_value("Java从入门到精通");
    std::ostringstream ss;
    doc.save(ss);
    std::string output = ss.str();
    EXPECT_TRUE(output.size() > 0);
}

#endif