#include "Action.h"

namespace GOAP
{
    Action::Action(Character& puppet) :
        m_Puppet(&puppet),
        m_ActionState(ActionState::DORMANT)
    {}

    void Action::StartAction()
    {
        m_ActionState = ActionState::ACTIVE;
        OnStartAction();
    }

    ActionState Action::GetActionState() const { return m_ActionState; }
    void Action::NotifyActionComplete() { m_ActionState = ActionState::COMPLETE; }
    void Action::NotifyActionFailed() { m_ActionState = ActionState::FAILED; }

    Character& Action::GetPuppet() { return *m_Puppet; }
}