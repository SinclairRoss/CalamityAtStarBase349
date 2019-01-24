#pragma once

#include <vector>

#include "Core\Math\Matrix4.h"
#include "Core\UI\UIElement_TextBox.h"
#include "GameConstants\FontData\FontName.h"

class RenderGroup_Text
{
    public:
        void AddText(const UIElement_TextBox& textBox);
        void Clean();

        int GetInstanceCount() const;

        const Matrix4& GetTransform(int i) const;
        const std::string& GetText(int i) const;
        FontName GetFontName(int i) const;

    private:
        template<typename T> void AddToList(std::vector<T>& list, const T& obj)
        {
            if (m_InstanceCount < list.size()) 
            { 
                list[m_InstanceCount] = obj; 
            }
            else 
            { 
                list.push_back(obj); 
            }
        }

        std::vector<Matrix4> m_Transforms;
        std::vector<std::string> m_Strings;
        std::vector<FontName> m_FontName;

        size_t m_InstanceCount;
};
