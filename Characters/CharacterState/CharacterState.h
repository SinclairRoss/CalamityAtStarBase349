#pragma once

#include <vector>

#include "Core\Preprocessor\BoilerPlate.h"
#include "Core\Math\Vector.h"

#include "GameObjects\Interactables\Interactable.h"

class CharacterState
{
    public:
        CharacterState();
        BOILERPLATE_DESTMOVECOPY(CharacterState)

        // Position
        void UpdatePosition(const Vector2& position);
        const Vector2& GetPosition(Vector2& position) const;

        // Interaction Candidates
        void UpdateInteractionCandidates(std::vector<Interactable*>& candidates);
        void UpdateInteractionCandidates(std::vector<Interactable*>&& candidates);
        bool IsViableInteractionCandidate(const Interactable& interactable) const;
        std::vector<Interactable*> GetInteractionCandidates();
        Interactable* GetClosestCandidate();

    private:
        Vector2 m_Position;
        std::vector<Interactable*> m_InteractionCandidates;
};