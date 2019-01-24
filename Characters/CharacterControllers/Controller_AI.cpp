#include "Controller_AI.h"

Controller_AI::Controller_AI(Character&& puppet, Map& map) :
    m_Puppet(std::move(puppet)),
    m_Navigator(m_Puppet, map),
    m_Planner(m_Puppet, m_Navigator, map),
    m_ActivePlan()
{}

void Controller_AI::Update()
{
    m_Puppet.UpdateCharacterState();

    m_Navigator.Update();

   if (m_ActivePlan.empty())
   {
       m_ActivePlan = m_Planner.CreatePlan();
   
       if (!m_ActivePlan.empty())
       {
           m_ActivePlan.back()->StartAction();
       }
   }
   
   if (!m_ActivePlan.empty())
   {
       GOAP::Action* activeAction = m_ActivePlan.back().get();
       activeAction->UpdateAction();
   
       GOAP::ActionState actionState = activeAction->GetActionState();
       switch (actionState)
       {
           case GOAP::ActionState::FAILED: 
           {
               m_ActivePlan.clear();
               break; 
           }
           case GOAP::ActionState::COMPLETE: 
           { 
               m_ActivePlan.pop_back();
               if (!m_ActivePlan.empty())
               {
                   m_ActivePlan.back()->StartAction();
               }
               break;
           }
       }
   }
}

void Controller_AI::ForceAction(std::unique_ptr<GOAP::Action> action)
{
    GOAP::ActionStack plan;
    plan.emplace_back(std::move(action));

    m_ActivePlan = std::move(plan);
    m_ActivePlan.at(0)->StartAction();
}

Character& Controller_AI::GetPuppet() { return m_Puppet; }
Navigator& Controller_AI::GetNavigator() { return m_Navigator; }