#pragma once

#include "GameState.h"

#include "Core\InputHandling\InputMapping\MappedInput.h"

class GameState_MainMenu : public GameState 
{
    public:
        GameState_MainMenu(Input::InputDeviceHandler& inputHandler);
        ~GameState_MainMenu();

        void Update(RenderPackage& renderPackage) override;

        void InputCallback(const Input::MappedInput& inputs);

    private:
};
