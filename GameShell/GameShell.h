// name: GameShell
// date: 05/01/2017
// Note: GameShell serves to hold all game related in a nice self contained space. 

#pragma once

#include <memory>
#include <SDL.h>

#include "Core\InputHandling\InputDeviceHandler.h"
#include "Core\RenderPackage\RenderPackageDistributor.h"
#include "GameStates\GameStateContainer.h"
#include "Renderer\GLRenderer.h"

#include "TimeKeepers\Timer_RealTime.h"
#include "TimeKeepers\Timer_TickPerSec.h"

#include "Core\UI\GUIPage.h"

class InputDevice;

class GameShell
{
    public:
        GameShell(SDL_Window& window);

        void RunGame();
        void StopGame();

    private:
        void PollEvents();

        void DebugOutput();

        bool m_GameRunning;

        GUIPage m_DebugPage;
        UIElement_TextBox* m_FPSTextBox;

		Input::InputDeviceHandler m_InputDeviceHandler;

		//SDL_Thread* m_RenderThread;
		GLRenderer m_Renderer;
		GameStateContainer m_GameStateContainer;

        RenderPackageDistributor m_RenderPackageDistributor;
        Timer_TickPerSec m_FPSCounter;
};