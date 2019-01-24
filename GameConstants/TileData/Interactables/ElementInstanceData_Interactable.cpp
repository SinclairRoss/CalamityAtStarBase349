#include "ElementInstanceData_Interactable.h"

ElementInstanceData_Interactable::ElementInstanceData_Interactable(std::string&& name, std::unique_ptr<InteractableEffect> effect) :
    m_Name(std::forward<std::string>(name)),
    m_Effect(std::move(effect))
{}