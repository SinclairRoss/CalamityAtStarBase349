#pragma once

#include <memory>

#include "Action\Action.h"
#include "Characters\Character.h"
#include "Map\Map.h"
#include "Utils\Types.h"
#include "AI\SubSystems\Navigator.h"

#include "ActionNodeGraph.h"

namespace GOAP
{
    class Planner
    {
        public:
            Planner(Character& puppet, Navigator& navigator, Map& map);

            ActionStack CreatePlan();

        private:
            Character* m_Puppet;
            Navigator* m_Navigator;
            Map* m_Map;

            static ActionNodeGraph ActionGraph;
    };
}