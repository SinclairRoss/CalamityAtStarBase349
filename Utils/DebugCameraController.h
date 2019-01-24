#pragma once

#include "Core\Camera\Camera.h"
#include "Core\InputHandling\InputMapping\MappedInput.h"

class DebugCameraController
{
    public:
        DebugCameraController(Camera& camera);
        
        void ParseInput(const Input::MappedInput& inputs);

    private:
        float m_ZoomSpeed;
        const float m_PanSpeed;
        Camera& m_Camera;
};
