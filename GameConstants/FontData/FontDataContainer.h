#pragma once

#include <memory>
#include <vector>

#include "FontData.h"
#include "FontName.h"

class FontDataContainer
{
    public:
        FontDataContainer();

        const FontData& GetFontDataWithName(FontName fontName) const;
        
        FontName StringToFontName(const std::string& string) const;
        std::string FontNameToString(FontName fontName) const;

        int FontCount() const;

    private:
        std::vector<std::unique_ptr<FontData>> m_Fonts;
};