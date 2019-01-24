#include "GameState_GOAPTest.h"

#include "Algorithms\AStar\AStar.h"
#include "AI\GOAP\Action\Action_MoveTo.h"
#include "GameConstants\GameConstants.h"
#include "Map\LoadingSaving\MapLoader.h"

#include "Core/Physics/Collisions/ColliderRegister/RigidBodyRegister.h"

GameState_GOAPTest::GameState_GOAPTest(Input::InputDeviceHandler& inputHandler) :
    GameState(inputHandler),
    m_Camera(),
    m_DebugCameraController(m_Camera),
    m_Map(MapLoader::LoadMap("GOAPTest")),
    m_UIOverlay(nullptr),
    m_AIController(Character(GameConstants::TextureData.GetIDWithName("Character_Chloe"), m_Map, Vector2(1.5f, 1.5f)), m_Map)
{
    m_Camera.SetZoom(0.1f);
    m_Camera.Translate(5, 5);

    m_InputDeviceHandler->AddContext("InputContext_PathingTest");
    m_InputDeviceHandler->AddInputCallback([this](const Input::MappedInput& inputs) {InputCallback(inputs); }, 0);

    m_UIOverlay = std::make_unique<GUIPage>(GameConstants::GUIPageData.GetPageData("Page_GOAPTest"));
}

GameState_GOAPTest::~GameState_GOAPTest()
{
    m_InputDeviceHandler->ClearContextStack();
    m_InputDeviceHandler->ClearInputCallbacks();
}

void GameState_GOAPTest::Update(RenderPackage& renderPackage)
{
    renderPackage.SetMainCamera(m_Camera);

    m_AIController.Update();
    RigidBodyRegister::UpdatePhysics();
}

void GameState_GOAPTest::InputCallback(const Input::MappedInput& inputs)
{
    m_DebugCameraController.ParseInput(inputs);
}

void GameState_GOAPTest::CheekyClearTileColours()
{
    m_Map.ForeachLevel([](MapLayer& layer)
    {
        layer.ForeachElement<MapElement_Floor>([](MapElement_Floor* element)
        {
            if (element != nullptr)
            {
                element->GetSprite().SetColour(ColourLibrary::White);
            }
        });
    });
}
