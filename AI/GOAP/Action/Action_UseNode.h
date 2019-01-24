#pragma once

#include "Action.h"

#include "AI\Node\AINode.h"

namespace GOAP
{
    class Action_UseNode : public Action
    {
        public:
            Action_UseNode(Character& puppet, AINode& node);

            void OnStartAction() override;
            void UpdateAction() override;

        private:
            AINode* m_Node;
    };
}