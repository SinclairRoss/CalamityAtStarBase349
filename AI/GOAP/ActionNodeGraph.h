#pragma once

#include <vector>

#include "Algorithms\AStar\AStarNode.h"
#include "Action\Action.h"
#include "Action\Action_InteractWith.h"
#include "Action\Action_MoveTo.h"

class ActionNodeGraph
{
    public:
        ActionNodeGraph();

    private:
        std::vector<std::unique_ptr<GOAP::Action>> m_ActionList;
};