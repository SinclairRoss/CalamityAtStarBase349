#include "ElementData.h"

#include "GameConstants\GameConstants.h"

ElementData::ElementData(const std::string& name, int textureID, float size_x, float size_y, float posOffset_x, float posOffset_y) :
    m_Name(name),
    m_TextureID(textureID),
    m_Size(size_x, size_y),
    m_PositionOffset(posOffset_x, posOffset_y)  
   // m_PositionOffset(((size_x/2.0f)-0.5f)+posOffset_x, ((size_y/2.0f)-0.5f)+posOffset_y)    // I am confused about this piece of code. I'm not sure we need it. well if we do there's probably a better way. Also I wrote this.
{}

const std::string& ElementData::GetName() const
{
    return m_Name;
}

int ElementData::GetTextureID() const
{
    return m_TextureID;
}

const Vector2& ElementData::GetSize() const
{
    return m_Size;
}

const Vector2& ElementData::GetPositionOffset() const
{
    return m_PositionOffset;
}
