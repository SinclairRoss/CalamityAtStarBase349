#include "InteractableSensor.h"

#include "Core\Physics\Collisions\ColliderRegister\InteractionBoundsRegister.h"

InteractableSensor::InteractableSensor(Collider* collider, CharacterState& characterState) :
    m_InteractableCollider(collider),
    m_CharacterState(&characterState)
{}

void InteractableSensor::Update()
{
    std::vector<Interactable*> candidates = InteractionBoundsRegister::DetectCollisions_Simple<Interactable>(m_InteractableCollider);
    m_CharacterState->UpdateInteractionCandidates(std::move(candidates));
}

void InteractableSensor::OnMoveOperation(Collider* collider, CharacterState& characterState)
{
    m_InteractableCollider = collider; 
    m_CharacterState = &characterState;
}