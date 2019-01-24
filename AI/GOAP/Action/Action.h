#pragma once

#include "ActionState.h"

#include "Core\InputHandling\InputMapping\MappedInput.h"
#include "Characters\Character.h"
#include "Core\Preprocessor\BoilerPlate.h"

namespace GOAP
{
    class Action
    {
        public:
            Action(Character& puppet);
            virtual ~Action() = default;
            BOILERPLATE_MOVECOPY(Action)

            void StartAction();
            virtual void OnStartAction() = 0; 
            virtual void UpdateAction() = 0;

            ActionState GetActionState() const;

        protected:
            void NotifyActionComplete();
            void NotifyActionFailed();

            Character& GetPuppet();

        private:
            Character* m_Puppet;
            ActionState m_ActionState;
    };
}