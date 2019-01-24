#include "GameState_MapTest.h"

#include "GameConstants\GameConstants.h"
#include "Core\EventHandlers\EventHandlers.h"
#include "Core\TestObjects\PointMarker.h"
#include "Core\Utils\ColourLibrary.h"
#include "Map\LoadingSaving\MapLoader.h"

#include "Core\Physics\Collisions\ColliderRegister\InteractionBoundsRegister.h"
#include "Core/Physics/Collisions/ColliderRegister/RigidBodyRegister.h"

GameState_MapTest::GameState_MapTest(Input::InputDeviceHandler& inputHandler) :
    GameState(inputHandler),
    m_Camera(),
    m_Starbase349(MapLoader::LoadMap("NewMap")),
    m_DebugCameraController(m_Camera),
    m_UserInput()
{
    m_Camera.SetZoom(0.3f);
    m_Camera.Translate(0, 0);

    m_InputDeviceHandler->AddContext("InputContext_LevelEditor");
    m_InputDeviceHandler->AddInputCallback([this](const Input::MappedInput& inputs) {InputCallback(inputs); }, 0);
}

GameState_MapTest::~GameState_MapTest()
{
    m_InputDeviceHandler->ClearContextStack();
    m_InputDeviceHandler->ClearInputCallbacks();
}

void GameState_MapTest::Update(RenderPackage& renderPackage)
{
    m_DebugCameraController.ParseInput(m_UserInput);
    RigidBodyRegister::UpdatePhysics();

    renderPackage.SetMainCamera(m_Camera);
}

void GameState_MapTest::InputCallback(const Input::MappedInput& inputs)
{
    m_UserInput = inputs;
}
