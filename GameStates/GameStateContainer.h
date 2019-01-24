// name: GameStateContainer
// date: 25/01/2017
// Note: Contains the different game states and is responsible for controlling which state is active at any given time.
//       GameStates changes are queued to allow the container to enter a safe state before actually switching.
//       Not doing this can cause fatal errors such as a gamestates cleanUp function clearing the callback stack while it is being iterated over.

#pragma once

#include <memory>

#include "Enums\GameStates.h"
#include "States\GameState.h"

namespace Input
{
    class InputDeviceHandler;
}

class GameStateContainer
{
    public:
        GameStateContainer(Input::InputDeviceHandler& inputDeviceHandler);

        GameStateContainer(const GameStateContainer&) = delete;
        GameStateContainer& operator= (const GameStateContainer&) = delete;

        GameStateContainer(GameStateContainer&&) = delete;
        GameStateContainer& operator= (GameStateContainer&&) = delete;

        void Update(RenderPackage& renderPackage);
        void ChangeState(GameStates gameState);

    private:
        
        std::unique_ptr<GameState> m_ActiveGameState;
        Input::InputDeviceHandler& m_InputDeviceHandler;
};
