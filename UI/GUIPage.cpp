#include "GUIPage.h"

#include "GameConstants\GameConstants.h"
#include "UIHelpers.h"

GUIPage::GUIPage(const rapidxml::xml_document<>* pageData)
{
    if (pageData != nullptr)
    {
        rapidxml::xml_node<>* rootNode = pageData->first_node();
        for (rapidxml::xml_node<> *element = rootNode->first_node(); element != nullptr; element = element->next_sibling())
        {
            std::string name(element->name());

            if (name == "TextBox")
            {
                std::string elementID = element->first_node("ID")->value();
                m_TextBoxes.insert(std::make_pair(elementID, UIHelpers::CreateTextBox(element)));
            }
        }
    }
    else
    {
        printf("GUIPage: Attempted to construct Page with nullptr.\n");
    }
}

UIElement_TextBox* GUIPage::GetTextBoxWithID(const std::string& id)
{
    auto pair = m_TextBoxes.find(id);
    return pair != m_TextBoxes.end() ? &pair->second : nullptr;
}

