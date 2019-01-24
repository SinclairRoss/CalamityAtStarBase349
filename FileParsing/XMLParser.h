#pragma once

#include <memory>
#include <string>

#include "rapidxml.hpp"

namespace XMLParser
{
    using XMLDoc_ptr = std::unique_ptr<rapidxml::xml_document<>>;

    extern XMLDoc_ptr ReadFile(std::string path);
    extern XMLDoc_ptr CreateXMLDoc();
    extern void SaveXMLToFile(XMLDoc_ptr& doc, const std::string& path, const std::string& name);

    extern int CalculateChildCount(const rapidxml::xml_node<>& parent);
}