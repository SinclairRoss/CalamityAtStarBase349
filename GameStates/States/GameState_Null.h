#pragma once

#include "GameState.h"

class GameState_Null : public GameState
{
    public:
        GameState_Null(Input::InputDeviceHandler& inputHandler);

        void Update(RenderPackage& renderPackage) override;
};
