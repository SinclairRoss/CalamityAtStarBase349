// name: GameState
// date: 05/01/2017
// Note: An abstract base class representing a "GameState". e.g the main menu, paused, playing, loading etc.

#pragma once

#include "Core\RenderPackage\RenderPackage.h"
#include "Core\InputHandling\InputDeviceHandler.h"

class GameState
{
	public:
        GameState(Input::InputDeviceHandler& inputHandler);
		virtual ~GameState();

        GameState(const GameState&) = delete;
        GameState& operator=(const GameState&) = delete;

        GameState(GameState&&) = delete;
        GameState& operator=(GameState&&) = delete;

		virtual void Update(RenderPackage& renderPackage) = 0;

    protected:
        Input::InputDeviceHandler* m_InputDeviceHandler;

	private:

};