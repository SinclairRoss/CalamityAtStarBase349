#pragma once

#include "Core\Physics\Collisions\CollisionDetection\Colliders\Collider_Sphere.h"

#include "Map\MapElements\MapElement.h"
#include "GameConstants\TileData\Interactables\ElementData_Interactable.h"
#include "GameConstants\TileData\Interactables\ElementInstanceData_Interactable.h"
#include "Core\Physics\RigidBody.h"

#include "Effects\InteractableEffect.h"
#include "AI\Node\AINode.h"
#include "Core\Preprocessor\BoilerPlate.h"

class Interactable : public MapElement
{
    public:
        Interactable(const ElementData_Interactable& data, ElementInstanceData_Interactable& instanceData, const Vector2& startingPos, int rotationIndex);
        virtual ~Interactable();

        BOILERPLATE_COPY(Interactable)

        Interactable(Interactable&&) noexcept;
        Interactable& operator=(Interactable&&) noexcept;

        virtual void Interact();

    private:

        std::unique_ptr<InteractableEffect> m_Effect;
        Collider_Sphere m_InteractionBounds;
        RigidBody m_RigidBody;
        AINode m_AINode;
};