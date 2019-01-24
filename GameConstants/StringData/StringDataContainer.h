#pragma once

#include <string>
#include <unordered_map>

class StringDataContainer
{
    public:
        StringDataContainer();
        const std::string* GetString(const std::string& name) const;

    private:

        std::unordered_map<std::string, const std::string> m_Strings;
};
