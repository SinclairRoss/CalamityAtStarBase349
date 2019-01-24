// name: GameState_PlayNoPlayer
// date: 05/01/2017
// Note: A game state representing the main game.

#pragma once

#include "GameState.h"

#include "Core\InputHandling\InputMapping\MappedInput.h"	
#include "Characters\Character.h"		               
#include "Core\Utils\DebugCameraController.h"
#include "Map\Map.h"

class GameState_MapTest : public GameState
{
    public:
        GameState_MapTest(Input::InputDeviceHandler& inputHandler);
        ~GameState_MapTest();

        void Update(RenderPackage& renderPackage) override;

        void InputCallback(const Input::MappedInput& inputs);

    private:
        Camera m_Camera;
        Map m_Starbase349;

        DebugCameraController m_DebugCameraController;

        Input::MappedInput m_UserInput;
};
