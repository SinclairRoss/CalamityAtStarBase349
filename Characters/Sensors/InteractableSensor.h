#pragma once

#include <vector>

#include "GameObjects\Interactables\Interactable.h"
#include "Characters\CharacterState\CharacterState.h"

class InteractableSensor
{
    public:
        InteractableSensor(Collider* collider, CharacterState& characterState);

        void Update();
        void OnMoveOperation(Collider* collider, CharacterState& characterState);

    private:
        Collider* m_InteractableCollider;
        CharacterState* m_CharacterState;
};