#include "Planner.h"

#include <memory>

#include "Action/Action_MoveTo.h"

namespace GOAP
{
    Planner::Planner(Character& puppet, Navigator& navigator, Map& map) :
        m_Puppet(&puppet),
        m_Navigator(&navigator),
        m_Map(&map)
    {}

    ActionStack Planner::CreatePlan()
    {
        ActionStack plan;
        
        Vector2 destination(6.5f, 5.5f);
        MapElement_Floor* destinationTile = m_Map->GetMapLayer(0).GetElementAt<MapElement_Floor>(destination);

        plan.emplace_back(std::make_unique<Action_MoveTo>(*m_Puppet, *m_Navigator, destination));

        return plan;
    }
}