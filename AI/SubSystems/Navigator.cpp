#include "Navigator.h"

#include "Algorithms\AStar\AStar.h"
#include "Algorithms\AStar\Utils.h"

Navigator::Navigator(Character& puppet, Map& map) :
    m_Puppet(&puppet),
    m_Map(&map),
    m_Path(),
    m_NodeReachedThreshold_Sqr(0.01f * 0.01f)
{}

bool Navigator::SetDestination(Vector2& destination)
{
    AStarNode<MapElement_Floor>* originNode = m_Map->GetMapLayer(0).GetPathingNode(m_Puppet->GetPosition());
    AStarNode<MapElement_Floor>* destinationNode = m_Map->GetMapLayer(0).GetPathingNode(destination);

    m_Path = AStar::Path<MapElement_Floor, true>(*originNode, *destinationNode);
   // AStar::TrimPath(m_Path, m_Puppet->GetCharacterBoundsRadius());

    return true;    // Returns true if a valid path has been found. add at later date.
}

bool Navigator::SetDestination(Interactable& interactable)
{
    return true;
}

void Navigator::Update()
{
    if (!m_Path.empty())
    {
        MapElement* nextStep = m_Path.back();
        Vector2 toNextStep = nextStep->GetPosition() - m_Puppet->GetPosition();
        m_Puppet->GetActiveMovementBehaviour().ParseInput(toNextStep.X, toNextStep.Y);

        if (toNextStep.CalculateLength_Sqr() < m_NodeReachedThreshold_Sqr)
        {
            m_Path.pop_back();
        }
    }
    else
    {
        m_Puppet->GetActiveMovementBehaviour().ParseInput(0,0);
    }
}
