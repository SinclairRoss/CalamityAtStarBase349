#pragma once

#include <string>

#include "Core\Math\Vector.h"

// Notes - Defines what an object looks like and how it is placed in the world.

class ElementData
{
    public:
        ElementData(const std::string& name, int textureID, float size_x, float size_y, float posOffset_x, float posOffset_y);
        virtual ~ElementData() = default;

        const std::string& GetName() const;
        int GetTextureID() const;
        const Vector2& GetSize() const;
        const Vector2& GetPositionOffset() const;

    private:

        const std::string m_Name;
        int m_TextureID;

        Vector2 m_Size;
        Vector2 m_PositionOffset;


};
