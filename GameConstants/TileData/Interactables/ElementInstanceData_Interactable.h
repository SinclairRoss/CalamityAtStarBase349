#pragma once

#include <memory>
#include <string>

#include "GameObjects\Interactables\Effects\InteractableEffect.h"

class ElementInstanceData_Interactable
{
    public:
        ElementInstanceData_Interactable(std::string&& name, std::unique_ptr<InteractableEffect> effect);

        const std::string& GetName() { return m_Name; }
        std::unique_ptr<InteractableEffect> MoveEffect() { return std::move(m_Effect); }

    private:
        std::string m_Name;
        std::unique_ptr<InteractableEffect> m_Effect;
};