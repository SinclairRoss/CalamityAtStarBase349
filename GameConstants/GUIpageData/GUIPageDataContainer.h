#pragma once

#include <unordered_map>
#include <string>

#include "Core\FileParsing\XMLParser.h"

class GUIPageDataContainer
{
    public:
        GUIPageDataContainer();

        const rapidxml::xml_document<>* GetPageData(std::string&& pageName) const;
        const rapidxml::xml_document<>* GetPageData(std::string& pageName) const;
        
    private:

        std::unordered_map<std::string, XMLParser::XMLDoc_ptr> m_PageData;
};