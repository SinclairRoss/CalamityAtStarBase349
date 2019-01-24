#pragma once

class InteractableEffect
{
    public:
        InteractableEffect();
        virtual ~InteractableEffect() = default;

        InteractableEffect(const InteractableEffect&) = default;
        InteractableEffect& operator=(const InteractableEffect&) = default;
        InteractableEffect(InteractableEffect&&) noexcept = default;
        InteractableEffect& operator=(InteractableEffect&&) noexcept = default;

        virtual void OnInteraction() = 0;
};
