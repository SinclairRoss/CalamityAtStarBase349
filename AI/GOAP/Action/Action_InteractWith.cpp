#include "Action_InteractWith.h"

namespace GOAP
{
    Action_InteractWith::Action_InteractWith(Character& puppet, InteractableSensor& interactableSensor, Interactable& interactable) :
        Action(puppet),
        m_TargetInteractable(&interactable),
        m_InteractableSensor(&interactableSensor)
    {}

    void Action_InteractWith::OnStartAction()
    {}

    void Action_InteractWith::UpdateAction()
    {}
}