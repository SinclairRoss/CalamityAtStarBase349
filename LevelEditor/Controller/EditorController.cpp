#include <cmath>
#include <SDL.h>

#include "Core\Math\MathsHelper.h"
#include "EditorController.h"
#include "GameConstants\GameConstants.h"
#include "Core\Renderables\Sprite.h"
#include "Map\LoadingSaving\MapSaver.h"
#include "Map\LoadingSaving\MapLoader.h"
#include "Map/Utils/MapUtils.h"

EditorController::EditorController(Camera& camera, Map& map) :
    m_PanSpeed(0.005f),
    m_ZoomSpeed(0.01f),
    m_SnapGrid(),
    m_Brush_Floor(),
    m_ActiveBrush(&m_Brush_Floor),
    m_TileIndex(0),
    m_Camera(camera),
    m_Map(map),
    m_CameraController(camera)
{
    m_ActiveBrush->BrushSelected();
}

void EditorController::ParseInput(const Input::MappedInput& inputs)
{
    float cursor_X = inputs.GetRange(Input::Range::CURSOR_X);
    float cursor_Y = inputs.GetRange(Input::Range::CURSOR_Y);
    Vector2 worldPos = m_Camera.ScreenToWorldCoords(cursor_X, cursor_Y);

    const Vector2& cursorPos = m_SnapGrid.SnapCoordinates(worldPos);
    
    m_ActiveBrush->SetPosition(cursorPos);

    m_CameraController.ParseInput(inputs);

    if (inputs.IsPressed(Input::Action::HOTKEY_1))
    {
        SwapBrush(m_Brush_Floor);
    }

    if (inputs.IsPressed(Input::Action::HOTKEY_2))
    {
        SwapBrush(m_Brush_Wall);
    }
    
    if (inputs.IsPressed(Input::Action::HOTKEY_3))
    {
      //  SwapBrush(m_Brush_StaticObj);
    }

    if (inputs.IsPressed(Input::Action::HOTKEY_4))
    {
        SwapBrush(m_Brush_Interactable);
    }

    if (inputs.IsPressed(Input::Action::HOTKEY_8))
    {
        m_Map = MapLoader::LoadMap("NewMap");
        printf("Loaded Map: NewMap\n");
    }
    
	if (inputs.IsPressed(Input::Action::HOTKEY_7))
	{
        MapUtils::CalculateFloorTileNeighbourhoods(m_Map);
        MapUtils::GenerateBounds(m_Map);
		printf("Generating map data\n");
	}

    if (inputs.IsPressed(Input::Action::HOTKEY_9))
    {
        MapSaver::SaveMap(m_Map);
        printf("Map Saved\n");
    }

    if (inputs.IsPressed(Input::Action::ROTATE_CW))
    {
        m_ActiveBrush->RotateClockwise();
    }

    if (inputs.IsPressed(Input::Action::ROTATE_CCW))
    {
        m_ActiveBrush->RotateCounterClockwise();
    }

    if (inputs.IsHeld(Input::Action::INTERACT))
    {
        m_ActiveBrush->CreateObject(m_Map, m_ActiveLevel);
    }

    if (inputs.IsHeld(Input::Action::INTERACT_ALT))
    {
        m_ActiveBrush->DestroyObject(m_Map, m_ActiveLevel);
    }
    
    //if (inputs.IsPressed(Action::NAVIGATE_LEVEL_UP))
    //{
    //    ++m_ActiveLevel;
    //    if (m_ActiveLevel >= m_Map.GetLevelCount())
    //    {
    //        m_Map.AddNewLevel();
    //    }
    //}

    if (inputs.IsPressed(Input::Action::NAVIGATE_LEVEL_DOWN))
    {
        m_ActiveLevel = MathsHelper::Clamp(m_ActiveLevel - 1, 0, m_Map.GetLevelCount()-1);
    }

    if (inputs.IsPressed(Input::Action::SELECT_NEXT_MAP_ELEMENT))
    {
        m_ActiveBrush->NextElement();
    }

    if (inputs.IsPressed(Input::Action::SELECT_PREVIOUS_MAP_ELEMENT))
    {
        m_ActiveBrush->PreviousElement();
    }
}

void EditorController::SwapBrush(BrushBase& brush)
{
    if (m_ActiveBrush != &brush)
    {
        m_ActiveBrush->BrushDeselected();
        m_ActiveBrush = &brush;
        m_ActiveBrush->BrushSelected();
    }
}

int EditorController::GetActiveLevelIndex() const
{
    return m_ActiveLevel;
}