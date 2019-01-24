#pragma once

#include <unordered_map>

#include "Core\FileParsing\XMLParser.h"
#include "Core\UI\UIElement_TextBox.h"

class GUIPage
{
    public:
        GUIPage(const rapidxml::xml_document<>* pageData);

        GUIPage(const GUIPage&) = delete;
        GUIPage& operator=(const GUIPage&) = delete;

        GUIPage(GUIPage&&) = delete;
        GUIPage& operator=(GUIPage&&) = delete;

        UIElement_TextBox* GetTextBoxWithID(const std::string& id);

    private:
        std::unordered_map<std::string, UIElement_TextBox> m_TextBoxes;
};