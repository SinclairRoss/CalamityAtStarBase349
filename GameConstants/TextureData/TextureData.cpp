#include "TextureData.h"

TextureData::TextureData(const std::string& name, const std::string& path) :
    m_Name(name),
    m_Path(path)
{}

const std::string& TextureData::Name() const
{
    return m_Name;
}

const std::string& TextureData::Path() const
{
    return m_Path;
}