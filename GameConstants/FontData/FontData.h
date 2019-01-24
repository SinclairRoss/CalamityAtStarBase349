// Author: Sinclair Ross
// Name: ObjectContainer
// Date: 07/02/2017

#pragma once

#include <array>
#include <memory>
#include <string>

#include <glm\glm.hpp>
#include <GL\glew.h>

#include "FontName.h"
#include "GlyphData.h"

class FontData
{
    public:
        FontData(const std::string& fontName);

        const GlyphData* GetGlyphData(char glyph) const;
        std::string GetFontName() const;        

    private:
        using GlyphDataContainer = std::array<std::unique_ptr<GlyphData>, 128>;
        GlyphDataContainer m_GlyphDataContainer;

        std::string m_FontName;
};
