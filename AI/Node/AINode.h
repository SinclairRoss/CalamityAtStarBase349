#pragma once

#include "WorldState\WorldState.h"
#include "GameObjects\Interactables\Interactable.h"
#include "Characters\Character.h"

class AINode
{
    public:
        AINode(Vector2 pos, Interactable& interactable, WorldState::BooleanState target);
        bool UseNode(Character& puppet);
        bool CanUseNode(Character& puppet) const;

    private:
        Vector2 m_Position;
        Interactable* m_Interactable;
        WorldState::BooleanState m_Target;
        bool m_Value;
};
