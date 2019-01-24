#include "XMLParser.h"

#include <fstream>

#include "rapidxml_print.hpp"

XMLParser::XMLDoc_ptr XMLParser::ReadFile(std::string path)
{
    XMLDoc_ptr doc = nullptr;
    std::string fullPath = "Resources/GameData/" + path;

    std::ifstream file;
    file.open(fullPath, std::ios::in | std::ios::binary);

    if (file.is_open())
    {
        std::string contents;
        file.seekg(0, std::ios::end);
        contents.resize(static_cast<unsigned int>(file.tellg()));
        file.seekg(0, std::ios::beg);
        file.read(&contents[0], contents.size());

        doc = std::make_unique<rapidxml::xml_document<>>();
        char* text = doc->allocate_string(contents.c_str());
        doc->parse<0>(text);
    }
    else
    {
        printf("Failed to open file at: %s", path.c_str());
    }

    file.close();

    return doc;
}

XMLParser::XMLDoc_ptr XMLParser::CreateXMLDoc()
{
    XMLParser::XMLDoc_ptr doc = std::make_unique<rapidxml::xml_document<>>();
    rapidxml::xml_node<>* decl = doc->allocate_node(rapidxml::node_declaration);
    decl->append_attribute(doc->allocate_attribute("version", "1.0"));
    decl->append_attribute(doc->allocate_attribute("encoding", "UTF-8"));
    doc->append_node(decl);

    return doc;
}

extern void XMLParser::SaveXMLToFile(XMLParser::XMLDoc_ptr& doc, const std::string& path, const std::string& name)
{
    std::string xmlString;
    rapidxml::print(std::back_inserter(xmlString), *doc.get());

    std::ofstream out(path + "/" + name + ".xml");
    out << xmlString;
    out.close();
}

int XMLParser::CalculateChildCount(const rapidxml::xml_node<>& parent)
{
    int count = 0;
    for (rapidxml::xml_node<> *child = parent.first_node(); child != nullptr; child = child->next_sibling())
    {
        ++count;
    }

    return count;
}