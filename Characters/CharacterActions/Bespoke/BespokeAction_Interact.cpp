#include "BespokeAction_Interact.h"

#include "Core\Physics\Collisions\ColliderRegister\InteractionBoundsRegister.h"

BespokeAction_Interact::BespokeAction_Interact(InteractableSensor& interactableSensor) :
    m_InteractableSensor(&interactableSensor)
{}

void BespokeAction_Interact::Interact() { Interact(nullptr); }

void BespokeAction_Interact::Interact(Interactable* specifiedInteractable)
{
    // If there is a specified interactable and it is a valid option to interact with use that, if not use the closest interactable available.
  // Interactable* interactable = specifiedInteractable != nullptr && m_InteractableSensor->IsViableCandidate(*specifiedInteractable) ? specifiedInteractable : nullptr;
  //
  // if (interactable != nullptr)
  // {
  //     interactable->Interact();
  // }
}

