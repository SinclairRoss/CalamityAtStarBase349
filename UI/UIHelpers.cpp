#include "UIHelpers.h"

#include "GameConstants\GameConstants.h"

UIElement_TextBox UIHelpers::CreateTextBox(rapidxml::xml_node<>* rootNode)
{
    std::string textID = rootNode->first_node("Text")->value();
    std::string fontString = rootNode->first_node("Font")->value();
    FontName fontName = GameConstants::FontData.StringToFontName(fontString);

    const std::string* textPtr = GameConstants::StringData.GetString(textID);
    std::string text = textPtr != nullptr ? *textPtr : "<->";

    float x = GameConstants::Window.AspectRatio() * static_cast<float>(atof(rootNode->first_node("X")->value()));
    float y = static_cast<float>(atof(rootNode->first_node("Y")->value()));

    return UIElement_TextBox(text, fontName, x, y);
}