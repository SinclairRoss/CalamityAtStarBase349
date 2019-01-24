#pragma once

#include "InteractableEffect.h"
#include "WorldState\WorldState.h"

class InteractableEffect_ToggleState : public InteractableEffect
{
    public:
        InteractableEffect_ToggleState(WorldState::BooleanState worldState);

        void OnInteraction() override;

    private:
        WorldState::BooleanState m_WorldState;
};