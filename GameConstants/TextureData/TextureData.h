#pragma once

#include <string>

class TextureData
{
    public:
        TextureData(const std::string& name, const std::string& path);

        const std::string& Name() const;
        const std::string& Path() const;

    private:
        const std::string m_Name;
        const std::string m_Path;

};
