#pragma once

#include "Action.h"

#include "Map\Map.h"
#include "Characters\Character.h"
#include "AI\SubSystems\Navigator.h"

namespace GOAP
{
    class Action_MoveTo : public Action
    {
        public:
            Action_MoveTo(Character& puppet, Navigator& navigator, Vector2 position);
            ~Action_MoveTo() = default;
            BOILERPLATE_MOVECOPY(Action_MoveTo)

            void OnStartAction() override;
            void UpdateAction() override;

        private:
            Vector2 m_Destination;
            Navigator* m_Navigator;
    };
}