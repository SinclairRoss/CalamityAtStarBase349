#include "TextureDataContainer.h"

#include "Core\FileParsing\XMLParser.h"

TextureDataContainer::TextureDataContainer()
{
    XMLParser::XMLDoc_ptr textureData = XMLParser::ReadFile("TextureData/TextureData.xml");
    rapidxml::xml_node<> *root = textureData->first_node();   

    int textureCount = XMLParser::CalculateChildCount(*root);
    m_TextureData.reserve(textureCount);

    for (rapidxml::xml_node<> *child = root->first_node(); child != nullptr; child = child->next_sibling())
    {
        std::string name(child->first_attribute()->name());
        std::string path(child->first_attribute()->value());
        std::string fullPath("Resources/Textures/" + path);

        m_TextureData.emplace_back(name, fullPath);
    }
}

int TextureDataContainer::GetIDWithName(const std::string& name) const
{
    int id = 0;

    int numTextures = m_TextureData.size();
    for (int i = 0; i < numTextures; ++i)
    {
        if (m_TextureData[i].Name() == name)
        {
            id = i;
            break;
        }
    }

    return id;
}

const TextureData& TextureDataContainer::GetTextureDataWithID(int id) const
{
    return m_TextureData[id];
}

int TextureDataContainer::GetTextureCount() const
{
    return m_TextureData.size();
}