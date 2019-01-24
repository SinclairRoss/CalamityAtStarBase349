#pragma once

#include "GameObjects\Interactables\Interactable.h"
#include "../../Sensors/InteractableSensor.h"

class BespokeAction_Interact
{
    public:
        BespokeAction_Interact(InteractableSensor& interactableSensor);

        void Interact();
        void Interact(Interactable* specifiedInteractable);

    private:
        InteractableSensor* m_InteractableSensor;
};