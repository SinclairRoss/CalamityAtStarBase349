#include "CharacterState.h"

#include <algorithm> // std::find

CharacterState::CharacterState()
{}

// Position
void CharacterState::UpdatePosition(const Vector2& position) { m_Position = position; }
const Vector2& CharacterState::GetPosition(Vector2& position) const { return m_Position; }

// Interactable Candidates
void CharacterState::UpdateInteractionCandidates(std::vector<Interactable*>& candidates) { m_InteractionCandidates = candidates; }
void CharacterState::UpdateInteractionCandidates(std::vector<Interactable*>&& candidates) { m_InteractionCandidates = std::move(candidates); }
std::vector<Interactable*> CharacterState::GetInteractionCandidates() { return m_InteractionCandidates; }
bool CharacterState::IsViableInteractionCandidate(const Interactable& interactable) const { return std::find(m_InteractionCandidates.cbegin(), m_InteractionCandidates.cend(), &interactable) != m_InteractionCandidates.cend(); }
Interactable* CharacterState::GetClosestCandidate()
{
    Interactable* candidate = nullptr;
    float minDist = std::numeric_limits<float>::max();

    for (Interactable* obj : m_InteractionCandidates)
    {
        Vector2 toObj = obj->GetPosition() - m_Position;
        float dist = toObj.CalculateLength_Sqr();

        if (dist < minDist)
        {
            candidate = obj;
            minDist = dist;
        }
    }

    return candidate;
}