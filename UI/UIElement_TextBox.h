#pragma once

#include "UIElement.h"

#include <string>
#include <vector>

#include "GameConstants\FontData\FontName.h"

class UIElement_TextBox : public UIElement
{
    public:
        UIElement_TextBox(const std::string& text, FontName fontname, float x, float y);
        ~UIElement_TextBox();

        UIElement_TextBox(const UIElement_TextBox&) = delete;
        UIElement_TextBox& operator=(const UIElement_TextBox&) = delete;
       
        UIElement_TextBox(UIElement_TextBox&& other) noexcept;
        UIElement_TextBox& operator=(UIElement_TextBox&& other) noexcept;

        const std::string& GetText() const;
        FontName GetFontName() const;
        void SetPlaceholderValue(const std::string& key, const std::string& value);

    private:
        
        struct Placeholder
        {
            Placeholder(const std::string& key, size_t start, size_t end) :
                Key(key),
                Text("["+ key+ "]"),
                Start(start),
                Length(end - start)
            {}

            const std::string Key;
            std::string Text;

            const size_t Start;
            const size_t Length;
        };

        void ReformatText();

        std::string m_OriginalText;
        std::string m_Text;
        FontName m_FontName;

        std::vector<Placeholder> m_Placeholders;
};
