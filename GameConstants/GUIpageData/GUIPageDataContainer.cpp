#include "GUIPageDataContainer.h"

GUIPageDataContainer::GUIPageDataContainer()
{
    XMLParser::XMLDoc_ptr doc = XMLParser::ReadFile("UI/GUIPageList.xml");
    rapidxml::xml_node<> *root = doc->first_node();

    for (rapidxml::xml_node<> *child = root->first_node(); child != nullptr; child = child->next_sibling())
    {
        std::string name(child->first_attribute()->name());
        const std::string path(child->first_attribute()->value());

        XMLParser::XMLDoc_ptr doc = XMLParser::ReadFile("UI/" + path);

        m_PageData.insert(std::make_pair(name, std::move(doc)));
    }
}

const rapidxml::xml_document<>* GUIPageDataContainer::GetPageData(std::string&& pageName) const
{
    return GetPageData(pageName);
}

const rapidxml::xml_document<>* GUIPageDataContainer::GetPageData(std::string& pageName) const
{
    auto pair = m_PageData.find(pageName);
    return pair != m_PageData.end() ? pair->second.get() : nullptr;
}