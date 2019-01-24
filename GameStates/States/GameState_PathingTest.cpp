#include "GameState_PathingTest.h"

#include "Algorithms\AStar\AStar.h"
#include "AI\GOAP\Action\Action_MoveTo.h"
#include "GameConstants\GameConstants.h"
#include "Map\LoadingSaving\MapLoader.h"

#include "Core/Physics/Collisions/ColliderRegister/RigidBodyRegister.h"

GameState_PathingTest::GameState_PathingTest(Input::InputDeviceHandler& inputHandler) :
    GameState(inputHandler),
    m_Camera(),
    m_DebugCameraController(m_Camera),
    m_Map(MapLoader::LoadMap("PathingTest")),
    m_UIOverlay(nullptr),
    m_AIController(Character(GameConstants::TextureData.GetIDWithName("Character_Chloe"), m_Map, Vector2(1.5f, 1.5f)), m_Map)
{
    m_Camera.SetZoom(0.1f);
    m_Camera.Translate(5, 5);

    m_InputDeviceHandler->AddContext("InputContext_PathingTest");
    m_InputDeviceHandler->AddInputCallback([this](const Input::MappedInput& inputs) {InputCallback(inputs); }, 0);

    m_UIOverlay = std::make_unique<GUIPage>(GameConstants::GUIPageData.GetPageData("Page_PathingTest"));
}

GameState_PathingTest::~GameState_PathingTest()
{
    m_InputDeviceHandler->ClearContextStack();
    m_InputDeviceHandler->ClearInputCallbacks();
}

void GameState_PathingTest::Update(RenderPackage& renderPackage)
{
    renderPackage.SetMainCamera(m_Camera);

    m_AIController.Update();
    RigidBodyRegister::UpdatePhysics();
}

void GameState_PathingTest::InputCallback(const Input::MappedInput& inputs)
{
    m_DebugCameraController.ParseInput(inputs);

    if (inputs.IsPressed(Input::Action::INTERACT))
    {
        Vector2 clickPos_World = m_Camera.ScreenToWorldCoords(inputs.GetRange(Input::Range::CURSOR_X), inputs.GetRange(Input::Range::CURSOR_Y));
        AStarNode<MapElement_Floor>* node = m_Map.GetMapLayer(0).GetPathingNode(clickPos_World);
        
        if (node != nullptr)
        {
            CheekyClearTileColours();
            MapElement_Floor* element = m_Map.GetMapLayer(0).GetElementAt<MapElement_Floor>(clickPos_World);
            element->GetSprite().SetColour(ColourLibrary::Magenta);
            
            m_EndPoint = node;
            m_AIController.GetNavigator().SetDestination(Vector2(node->Data().GetPosition()));
        }
    }
}

void GameState_PathingTest::CheekyClearTileColours()
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
