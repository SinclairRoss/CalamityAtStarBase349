#include "Helpers.h"

#include "GameObjects\Interactables\Effects\InteractableEffect_ToggleState.h"

namespace MapLoader
{
    namespace Utils
    {
        std::unique_ptr<InteractableEffect> CreateInteractableEffect(rapidxml::xml_node<>* elementNode)
        {
            std::unique_ptr<InteractableEffect> effect = nullptr;

            if (elementNode->first_node("ToggleBooleanState"))
            {
                std::string val = elementNode->first_node("ToggleBooleanState")->value();
                WorldState::BooleanState state = WorldState::StringToBooleanState(val);

                effect = std::make_unique<InteractableEffect_ToggleState>(state);
            }
            else
            {
                printf("Unrecognised interactable effect.\n");
            }
           
            return effect;
        }
    }
}