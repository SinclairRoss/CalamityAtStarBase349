#pragma once

#include "Core\Camera\Camera.h"
#include "Core\InputHandling\InputMapping\MappedInput.h"
#include "Core\Utils\DebugCameraController.h"
#include "Map\Map.h"
#include "SnapGrid.h"

#include "LevelEditor\Brushes\Brush.h"

#include "glm/glm.hpp"

class EditorController
{
    public:
        EditorController(Camera& camera, Map& map);
       
        void ParseInput(const Input::MappedInput& inputs);

        int GetActiveLevelIndex() const;

    private:
        void SwapBrush(BrushBase& brush);

        float m_PanSpeed;
        float m_ZoomSpeed;

        SnapGrid m_SnapGrid;

        Brush<MapElement_Floor> m_Brush_Floor;
        Brush<MapElement_Wall> m_Brush_Wall;
        Brush<Interactable> m_Brush_Interactable;
       
        BrushBase* m_ActiveBrush;

        int m_TileIndex;
        int m_ActiveLevel;

        Camera& m_Camera;
        Map& m_Map;

        DebugCameraController m_CameraController;
};
