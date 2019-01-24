#include "GameState_MainMenu.h"

#include "Core\EventHandlers\PublisherSubscriber\BroadcastStation.h"
#include "GameConstants\GameConstants.h"
#include "Core\Utils\ColourLibrary.h"

GameState_MainMenu::GameState_MainMenu(Input::InputDeviceHandler& inputHandler) :
    GameState(inputHandler)
{
    m_InputDeviceHandler->AddContext("InputContext_Menu");
    m_InputDeviceHandler->AddInputCallback([this](const Input::MappedInput& inputs) {InputCallback(inputs); }, 0);
}

GameState_MainMenu::~GameState_MainMenu()
{
    m_InputDeviceHandler->ClearContextStack();
    m_InputDeviceHandler->ClearInputCallbacks();
}

void GameState_MainMenu::Update(RenderPackage& renderPackage)
{}

void GameState_MainMenu::InputCallback(const Input::MappedInput& inputs)
{
    if (inputs.IsPressed(Input::Action::MENU_NAVIGATE_DOWN))
        printf("Menu Navigate Down\n");

    if (inputs.IsPressed(Input::Action::MENU_NAVIGATE_UP))
        printf("Menu Navigate Up\n");

    if (inputs.IsPressed(Input::Action::MENU_SELECT))
    {
        printf("Menu Select\n");
    }

    if (inputs.IsPressed(Input::Action::MENU_CANCEL))
        printf("Menu Cancel\n");
}