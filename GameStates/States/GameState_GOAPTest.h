#pragma once

#include "GameState.h"

#include "Characters\Character.h"
#include "Core\Utils\ColourLibrary.h"
#include "Core\UI\GUIPage.h"
#include "Core\Utils\DebugCameraController.h"
#include "Map\Map.h"
#include "TimeKeepers\Timer_RealTime.h"
#include "Characters\CharacterControllers\Controller_AI.h"

#include "Core\TestObjects\PointMarker.h"

class GameState_GOAPTest : public GameState
{
public:
    GameState_GOAPTest(Input::InputDeviceHandler& inputHandler);
    ~GameState_GOAPTest();

    void Update(RenderPackage& renderPackage) override;

    void InputCallback(const Input::MappedInput& inputs);

private:
    void CheekyClearTileColours();

    Camera m_Camera;
    Map m_Map;

    DebugCameraController m_DebugCameraController;

    const AStarNode<MapElement_Floor>* m_StartPoint;
    const AStarNode<MapElement_Floor>* m_EndPoint;

    std::unique_ptr<GUIPage> m_UIOverlay;

    Controller_AI m_AIController;
};