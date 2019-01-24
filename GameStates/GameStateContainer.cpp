#include "GameStateContainer.h"

#include "States\GameState_MainMenu.h"
#include "States\GameState_Null.h"
#include "States\GameState_Play.h"
#include "States\GameState_PathingTest.h"
#include "States\GameState_LevelEditor.h"
#include "States\GameState_MapTest.h"
#include "States\GameState_PhysicsTest.h"
#include "States\GameState_GOAPTest.h"

GameStateContainer::GameStateContainer(Input::InputDeviceHandler& inputDeviceHandler) :
    m_ActiveGameState(nullptr),
    m_InputDeviceHandler(inputDeviceHandler)
{}

void GameStateContainer::ChangeState(GameStates gameState)
{
    m_ActiveGameState.reset();  // Calling reset ensures the previous state is deconstructed before the next state is created.

    switch (gameState)
    {
        case GameStates::MAIN_MENU: { m_ActiveGameState = std::make_unique<GameState_MainMenu>(m_InputDeviceHandler); break; }
        case GameStates::PLAY: { m_ActiveGameState = std::make_unique<GameState_Play>(m_InputDeviceHandler); break; }
        case GameStates::LEVEL_EDITOR: { m_ActiveGameState = std::make_unique<GameState_LevelEditor>(m_InputDeviceHandler); break; }
        case GameStates::PATHING_TEST: { m_ActiveGameState = std::make_unique<GameState_PathingTest>(m_InputDeviceHandler); break; }
        case GameStates::MAP_TEST: { m_ActiveGameState = std::make_unique<GameState_MapTest>(m_InputDeviceHandler); break; }
        case GameStates::PHYSICS_TEST: { m_ActiveGameState = std::make_unique<GameState_PhysicsTest>(m_InputDeviceHandler); break; }
        case GameStates::GOAP_TEST: { m_ActiveGameState = std::make_unique<GameState_GOAPTest>(m_InputDeviceHandler); break; }
        default: { printf("GameStateContainer::GetGameState - Unknown GameState selected!"); }
    }
}

void GameStateContainer::Update(RenderPackage& renderPackage)
{
    m_ActiveGameState->Update(renderPackage);
}