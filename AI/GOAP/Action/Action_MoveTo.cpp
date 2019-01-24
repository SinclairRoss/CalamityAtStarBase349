#include "Action_MoveTo.h"

#include "Algorithms\AStar\AStar.h"

namespace GOAP
{
    Action_MoveTo::Action_MoveTo(Character& puppet, Navigator& navigator, Vector2 destination) :
        Action(puppet),
        m_Navigator(&navigator),
        m_Destination(destination)
    {}

    void Action_MoveTo::OnStartAction()
    {
        bool pathFound = m_Navigator->SetDestination(m_Destination);
        if (!pathFound)
        {
            NotifyActionFailed();
        }
    }

    void Action_MoveTo::UpdateAction()
    {
        const Vector2& puppetPos = GetPuppet().GetPosition();
        const Vector2 toDestination(puppetPos - m_Destination);
        float distance = toDestination.CalculateLength_Sqr();
        if (distance <= 0.1f)
        {
            NotifyActionComplete();
        }
    }
}