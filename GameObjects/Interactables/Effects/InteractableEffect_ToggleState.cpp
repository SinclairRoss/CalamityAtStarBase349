#include "InteractableEffect_ToggleState.h"

InteractableEffect_ToggleState::InteractableEffect_ToggleState(WorldState::BooleanState worldState) :
    m_WorldState(worldState)
{}

void InteractableEffect_ToggleState::OnInteraction()
{
    WorldState::ToggleState(m_WorldState);
}