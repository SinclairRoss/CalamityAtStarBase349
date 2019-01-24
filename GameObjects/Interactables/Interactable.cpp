#include "Interactable.h"

#include "Core\Physics\Collisions\CollisionDetection\Colliders\Collider_AABB.h"
#include "Core\Preprocessor\Preprocessor.h"

#include "Effects\InteractableEffect_ToggleState.h"

Interactable::Interactable(const ElementData_Interactable& data, ElementInstanceData_Interactable& instanceData, const Vector2& startingPos, int rotationIndex) :
    MapElement(&data, startingPos, rotationIndex),
    m_InteractionBounds(GetTransform(), 1.0f, HIGHLIGHT_INTERACTABLE),
    m_RigidBody(GetTransform(), new Collider_AABB(GetTransform(), 0.5f, 0.5f, HIGHLIGHT_RIGIDBODY_STATIC, ColourLibrary::Highlight_RigidBody_Static), 0.0f, 0.0f),
    m_Effect(instanceData.MoveEffect()),
    m_AINode(startingPos + data.GetAIInteractionNodePositions[0], *this, WorldState::BooleanState::SWITCH_ON)
{}

Interactable::~Interactable()
{}

Interactable::Interactable(Interactable&& other) noexcept :
    MapElement(std::move(other)),
    m_InteractionBounds(std::move(other.m_InteractionBounds)),
    m_RigidBody(std::move(other.m_RigidBody))
{
    m_InteractionBounds.OnMoveOperation(GetTransform());
    m_RigidBody.OnMoveOperation(GetTransform());
}

Interactable& Interactable::operator=(Interactable&& other) noexcept
{
    if (this != &other)
    {
        MapElement::operator=(std::move(other));
        m_InteractionBounds = std::move(other.m_InteractionBounds);
        m_RigidBody = std::move(other.m_RigidBody);

        m_InteractionBounds.OnMoveOperation(GetTransform());
        m_RigidBody.OnMoveOperation(GetTransform());
    }

    return *this;
}

void Interactable::Interact()
{
    m_Effect->OnInteraction();
}
