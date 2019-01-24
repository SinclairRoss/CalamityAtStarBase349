#pragma once

#include "Action.h"

#include "Characters\Sensors\InteractableSensor.h"
#include "GameObjects\Interactables\Interactable.h"

namespace GOAP
{
    class Action_InteractWith : public Action
    {
        public:
            Action_InteractWith(Character& puppet, InteractableSensor& interactableSensor, Interactable& interactable);
            ~Action_InteractWith() = default;
            Action_InteractWith(const Action_InteractWith&) = default;
            Action_InteractWith& operator=(const Action_InteractWith&) = default;
            Action_InteractWith(Action_InteractWith&&) noexcept = default;
            Action_InteractWith& operator=(Action_InteractWith&&) noexcept = default;

            void OnStartAction() override;
            void UpdateAction() override;

        private:
            Interactable* m_TargetInteractable;
            InteractableSensor* m_InteractableSensor;
    };
}