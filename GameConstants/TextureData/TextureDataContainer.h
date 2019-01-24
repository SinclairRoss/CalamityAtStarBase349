#pragma once

#include <string>
#include <vector>

#include "TextureData.h"

class TextureDataContainer
{
    public:
        TextureDataContainer();

        int GetIDWithName(const std::string& name) const;
        const TextureData& GetTextureDataWithID(int id) const;

        int GetTextureCount() const;

    private:    
        std::vector<TextureData> m_TextureData;
};
