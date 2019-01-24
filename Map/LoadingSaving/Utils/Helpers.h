#pragma once

#include <memory>

#include "Core\FileParsing\XMLParser.h"
#include "GameObjects\Interactables\Effects\InteractableEffect.h"

namespace MapLoader
{
    namespace Utils
    {
        extern std::unique_ptr<InteractableEffect> CreateInteractableEffect(rapidxml::xml_node<>* elementNode);
    }
}