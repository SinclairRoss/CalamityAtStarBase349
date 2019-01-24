#include "UIElement_TextBox.h"

#include "Core\RenderRegister\ObjectRenderRegister.h"

UIElement_TextBox::UIElement_TextBox(const std::string& text, FontName fontname, float x, float y) :
    UIElement(x, y),
    m_OriginalText(text),
    m_Text(m_OriginalText),
    m_FontName(fontname)
{
	ObjectRenderRegister::RegisterObject<UIElement_TextBox>(*this);

    size_t start = m_OriginalText.find('[', 0);
    size_t end = m_OriginalText.find(']', 0);
    while (start != std::string::npos) 
    {
        std::string key = m_OriginalText.substr(start+1, end-start-1);
        m_Placeholders.emplace_back(key, start, end + 1);
        
        start = m_OriginalText.find('[', start+1);
        end = m_OriginalText.find(']', end+1);
    }
}

UIElement_TextBox::~UIElement_TextBox()
{
	ObjectRenderRegister::DeregisterObject<UIElement_TextBox>(*this);
}

UIElement_TextBox::UIElement_TextBox(UIElement_TextBox&& other) noexcept :
    UIElement(std::move(other)),
    m_OriginalText(std::move(other.m_OriginalText)),
    m_Text(std::move(other.m_Text)),
    m_FontName(other.m_FontName),
    m_Placeholders(std::move(other.m_Placeholders))
{
	ObjectRenderRegister::RegisterObject<UIElement_TextBox>(*this);
}

UIElement_TextBox& UIElement_TextBox::operator=(UIElement_TextBox&& other) noexcept
{
    if (&other != this)
    {
        UIElement::operator=(std::move(other));
        m_OriginalText = std::move(other.m_OriginalText);
        m_Text = std::move(other.m_Text);
        m_FontName = other.m_FontName;
        m_Placeholders = std::move(other.m_Placeholders);
    }

    return *this;
}

const std::string& UIElement_TextBox::GetText() const { return m_Text; }
FontName UIElement_TextBox::GetFontName() const { return m_FontName; }

void UIElement_TextBox::SetPlaceholderValue(const std::string& key, const std::string& value)
{
    for (Placeholder& ph : m_Placeholders)
    {
        if (ph.Key == key)
        {
            ph.Text = value;
        }
    }

    ReformatText();
}

void UIElement_TextBox::ReformatText()
{
    m_Text = m_OriginalText;
    for (std::vector<Placeholder>::reverse_iterator iter = m_Placeholders.rbegin(); iter != m_Placeholders.rend(); ++iter)
    {
        const Placeholder& ph = *iter;
        m_Text.replace(ph.Start, ph.Length, ph.Text);
    }
}