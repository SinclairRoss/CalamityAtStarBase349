#include "GameShell.h"

#include <iomanip> // setprecision
#include <sstream>
#include <string>

#include "Core\EventHandlers\PublisherSubscriber\BroadcastStation.h"
#include "GameConstants\GameConstants.h"
#include "TimeKeepers\Timer_DeltaTimer.h"
#include "Core\EventHandlers\EventHandlers.h"

#include "Core\Utils\Utils.h"
#include "Core\Utils\Vector2D.h"

GameShell::GameShell(SDL_Window& window) :
    m_GameRunning(true),
    m_DebugPage(GameConstants::GUIPageData.GetPageData("Page_Test")),
    m_FPSTextBox(m_DebugPage.GetTextBoxWithID("TextBox_FPS")),
	m_InputDeviceHandler(),
	m_Renderer(window),
	m_GameStateContainer(m_InputDeviceHandler),
    m_RenderPackageDistributor(m_Renderer.GetMaxInstanceCount())
{
    m_GameStateContainer.ChangeState(GameStates::GOAP_TEST);
}

void GameShell::RunGame()
{
    Timer_DeltaTimer deltaTimer;
    float accumulatedTime = 0.0f;

    while (m_GameRunning)
    {
        deltaTimer.Tick();
        float deltaTime = deltaTimer.GetDeltaTime();
        accumulatedTime += deltaTime;

        if (accumulatedTime >= GameConstants::DeltaTime_Real)
        {
            accumulatedTime -= GameConstants::DeltaTime_Real;

            RenderPackage* writePackage = nullptr;
            while (writePackage == nullptr)
            {
                writePackage = m_RenderPackageDistributor.Checkout_ForWrite();
            }

            PollEvents();
            m_InputDeviceHandler.Update();
            m_GameStateContainer.Update(*writePackage);
            writePackage->FillPackage();
            m_RenderPackageDistributor.Checkin_FromWrite(*writePackage);

            RenderPackage* readPackage = m_RenderPackageDistributor.Checkout_ForRead();
            if (readPackage != nullptr)
            {
                m_Renderer.Draw(*readPackage);
                m_RenderPackageDistributor.Checkin_FromRead(*readPackage);
            }

            DebugOutput();
        }
    }
}

#include "WorldState\WorldState.h"

void GameShell::DebugOutput()
{
    m_FPSCounter.Tick();
    double fps = m_FPSCounter.GetTicksPerSecond();

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << fps;
    m_FPSTextBox->SetPlaceholderValue("FPS", ss.str());
    
    //printf("SwitchOn: %s", WorldState::GetState(WorldState::BooleanState::SWITCH_ON) ? "On" : "Off");
}

void GameShell::StopGame()
{
    m_GameRunning = false;
}

void GameShell::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                StopGame();
                break;
            }
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        StopGame();
                        break;
                    }
                }

                break;
            }
            case SDL_CONTROLLERDEVICEADDED:
            {
                int index = event.cdevice.which;
                if (SDL_IsGameController(index))
                {
                    printf("Controller: %i connected!\n", index);
                }
                break;
            }
            case SDL_CONTROLLERDEVICEREMOVED:
            {
                printf("Controller removed!\n");
                break;
            }
        }

        m_InputDeviceHandler.OnSDLEvent(event);
    }

    while (EventHandlers::MainEventQueue.EventsRemaining())
    {
        EventType event = EventHandlers::MainEventQueue.PopQueue();

        switch (event)
        {
            case EventType::START_GAME:
            {
                printf("OnBroadcast_StartGame\n");
                m_GameStateContainer.ChangeState(GameStates::PLAY);

                break;
            }
            case EventType::QUIT_GAME:
            {
                printf("OnBroadcast_QuitGame\n");
                m_GameStateContainer.ChangeState(GameStates::LEVEL_EDITOR);

                break;
            }
            default:
            {
                printf("Event effect not defined\n");
                break;
            }
        }
    }
}