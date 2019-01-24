#include "FontDataContainer.h"

#include "Core\FileParsing\XMLParser.h"

//<Font>
//<FontName>Heading< / FontName>
//<FileName>Arkitech Light_35< / FileName>
//< / Font>
//<Font>
//<FontName>Body< / FontName>
//<FileName>Saniretro_35< / FileName>
//< / Font>

FontDataContainer::FontDataContainer()
{
    int fontCount = static_cast<int>(FontName::_COUNT);
    m_Fonts.resize(fontCount);

    XMLParser::XMLDoc_ptr doc = XMLParser::ReadFile("FontData/FontData.xml");
    rapidxml::xml_node<> *root = doc->first_node();

    for (rapidxml::xml_node<> *child = root->first_node(); child != nullptr; child = child->next_sibling())
    {
        std::string fontName_String = child->first_attribute()->name();
        FontName fontName = StringToFontName(fontName_String);

        if (fontName != FontName::_INVALID)
        {
            std::string fileName(child->first_attribute()->value());

            int index = static_cast<int>(fontName);
            if (m_Fonts[index] == nullptr)
            {
                m_Fonts[index] = std::make_unique<FontData>(fileName);
            }
            else
            {
                printf("Duplicate font in FontData.xml: %s\n", fontName_String.c_str());
            }
        }
        else
        {
            printf("FontName not found: %s\n", fontName_String.c_str());
        }
    }

    int numFonts = m_Fonts.size();
    for (int i = 0; i < numFonts; ++i)
    {
        if (m_Fonts[i] == nullptr)
        {
            FontName fontName = static_cast<FontName>(i);
            std::string fontName_String = FontNameToString(fontName);
            printf("Missing font: %s\n", fontName_String.c_str());
        }
    }
}

FontName FontDataContainer::StringToFontName(const std::string& string) const
{
    FontName font = FontName::_INVALID;

    if (string == "Body") { font = FontName::BODY; }
    else if (string == "Heading") { font = FontName::HEADING; }
    else { printf("FontName not found: %s\n", string.c_str()); }

    return font;
}

std::string FontDataContainer::FontNameToString(FontName fontName) const
{
    std::string name = "Name Not Found";

    switch (fontName)
    {
        case FontName::BODY: { name = "Body";  break; }
        case FontName::HEADING: { name = "Heading";  break; }

        case FontName::_INVALID: {name = "INVALID"; break; }
        case FontName::_COUNT: {name = "FONT_COUNT... You ding-a-ling!"; break; }
    }

    return name;
}

const FontData& FontDataContainer::GetFontDataWithName(FontName fontName) const
{
    int id = static_cast<int>(fontName);
    return *m_Fonts[id];
}

int FontDataContainer::FontCount() const
{
    return static_cast<int>(FontName::_COUNT);
}