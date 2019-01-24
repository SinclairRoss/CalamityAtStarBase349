#include "RenderGroup_Text.h"

void RenderGroup_Text::AddText(const UIElement_TextBox& textBox)
{
    AddToList<Matrix4>(m_Transforms, textBox.GetTransform());
    AddToList<std::string>(m_Strings, textBox.GetText());
    AddToList<FontName>(m_FontName, textBox.GetFontName());

    ++m_InstanceCount;
}

void RenderGroup_Text::Clean()
{
    m_InstanceCount = 0;
}

int RenderGroup_Text::GetInstanceCount() const { return m_InstanceCount; }

const Matrix4& RenderGroup_Text::GetTransform(int i) const { return m_Transforms[i]; }
const std::string& RenderGroup_Text::GetText(int i) const { return m_Strings[i]; }
FontName RenderGroup_Text::GetFontName(int i) const { return m_FontName[i]; };