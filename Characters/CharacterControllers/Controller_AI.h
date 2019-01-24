#pragma once

#include "AI\GOAP\Planner.h"
#include "AI\SubSystems\Navigator.h"
#include "Map\Map.h"

class Controller_AI
{
    public:
        Controller_AI(Character&& puppet, Map& map);

        void Update();

        void ForceAction(std::unique_ptr<GOAP::Action> action);
        Character& GetPuppet();

        Navigator& GetNavigator();

    private:
        Character m_Puppet;

        Navigator m_Navigator;

        GOAP::Planner m_Planner;
        GOAP::ActionStack m_ActivePlan;
};