#include "FontData.h"

#include <vector>

#include "Core\Math\MathsHelper.h"
#include "Core\FileParsing\XMLParser.h"
#include "GameConstants\GameConstants.h"

FontData::FontData(const std::string& fontName) :
    m_FontName(fontName)
{
    std::string path = "FontData/" + m_FontName + ".xml";
    XMLParser::XMLDoc_ptr doc = XMLParser::ReadFile(path);

    if (doc != nullptr)
    {
        rapidxml::xml_node<> *root = doc->first_node();
        for (rapidxml::xml_node<> *child = root->first_node("Glyph"); child != nullptr; child = child->next_sibling())
        {
            char glyph = child->first_node("Char")->value()[0]; 
            if (glyph == '\0')
            {
                glyph = ' ';
            }

            float tex_U = static_cast<float>(atof(child->first_node("Tex_U")->value()));
            float tex_V = static_cast<float>(atof(child->first_node("Tex_V")->value()));
            float tex_W = static_cast<float>(atof(child->first_node("Tex_W")->value()));
            float tex_H = static_cast<float>(atof(child->first_node("Tex_H")->value()));

            int glyph_Width = atoi(child->first_node("Glyph_Width")->value());
            int glyph_Height = atoi(child->first_node("Glyph_Height")->value());
            int glyph_AdvanceX = atoi(child->first_node("Glyph_AdvanceX")->value());
            int glyph_AdvanceY = atoi(child->first_node("Glyph_AdvanceY")->value());
            int glyph_BearingX = atoi(child->first_node("Glyph_BearingX")->value());
            int glyph_BearingY = atoi(child->first_node("Glyph_BearingY")->value());

            m_GlyphDataContainer[glyph] = std::make_unique<GlyphData>(glyph, tex_U, tex_V, tex_W, tex_H, glyph_Width, glyph_Height, glyph_AdvanceX, glyph_AdvanceY, glyph_BearingX, glyph_BearingY);
        }
    }
}

const GlyphData* FontData::GetGlyphData(char glyph) const
{
    return m_GlyphDataContainer[glyph].get();
}

std::string FontData::GetFontName() const
{
    return m_FontName;
}

