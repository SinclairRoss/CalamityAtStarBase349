#include "Action_UseNode.h"

namespace GOAP
{
    Action_UseNode::Action_UseNode(Character& puppet, AINode& node) :
        Action(puppet),
        m_Node(&node)
    {}

    void Action_UseNode::OnStartAction()
    {
        bool nodeUsed = m_Node->UseNode(GetPuppet());
        if (nodeUsed)
        {
            NotifyActionComplete();
        }
        else
        {
            NotifyActionFailed();
        }
    }

    void Action_UseNode::UpdateAction()
    {}
}