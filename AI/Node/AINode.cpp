#include "AINode.h"

AINode::AINode(Vector2 pos, Interactable& interactable, WorldState::BooleanState target) :
    m_Position(pos),
    m_Interactable(&interactable),
    m_Target(target),
    m_Value(!WorldState::GetState(target))
{}

bool AINode::UseNode(Character& puppet)
{
    bool canUseNode = CanUseNode(puppet);
    if (canUseNode)
    {
        m_Interactable->Interact();
    }

    return canUseNode;
}

bool AINode::CanUseNode(Character& puppet) const
{
    bool canUseNode = puppet.GetCharacterState().IsViableInteractionCandidate(*m_Interactable);
    return canUseNode;
}