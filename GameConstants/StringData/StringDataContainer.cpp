#include "StringDataContainer.h"

#include "Core\FileParsing\XMLParser.h"

StringDataContainer::StringDataContainer()
{
    XMLParser::XMLDoc_ptr doc = XMLParser::ReadFile("Strings/Strings_English.xml");
    rapidxml::xml_node<> *root = doc->first_node();

    for (rapidxml::xml_node<> *child = root->first_node(); child != nullptr; child = child->next_sibling())
    {
        const std::string name(child->first_attribute()->name());
        const std::string string(child->first_attribute()->value());

        std::pair<const std::string, const std::string> stringPair = std::make_pair(name, string);
        m_Strings.insert(stringPair);
    }
}

const std::string* StringDataContainer::GetString(const std::string& name) const
{
    auto pair = m_Strings.find(name);

    const std::string* string = pair != m_Strings.end() ? &pair->second : nullptr;
    return string;
}