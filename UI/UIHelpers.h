#pragma once

#include "Core\FileParsing\XMLParser.h"
#include "UIElement_TextBox.h"

namespace UIHelpers
{
    extern UIElement_TextBox CreateTextBox(rapidxml::xml_node<>* rootNode);
}