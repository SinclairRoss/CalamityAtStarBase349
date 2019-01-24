#include "DebugCameraController.h"

#include "GameConstants\GameConstants.h"

DebugCameraController::DebugCameraController(Camera& camera) :
    m_ZoomSpeed(0.01f),
    m_PanSpeed(5.0f),
    m_Camera(camera)
{}

void DebugCameraController::ParseInput(const Input::MappedInput& inputs)
{
    if (inputs.IsHeld(Input::Action::CAMERA_PAN_MODE))
    {
        float cursor_X = inputs.GetRange(Input::Range::CURSOR_X);
        float cursor_Y = inputs.GetRange(Input::Range::CURSOR_Y);
        Vector2 worldPos = m_Camera.ScreenToWorldCoords(cursor_X, cursor_Y);

        float previousCursorPos_X = cursor_X - inputs.GetRange(Input::Range::CURSOR_DELTA_X);
        float previousCursorPos_Y = cursor_Y - inputs.GetRange(Input::Range::CURSOR_DELTA_Y);

        Vector2 previousWorldPos = m_Camera.ScreenToWorldCoords(previousCursorPos_X, previousCursorPos_Y);
        Vector2 delta = previousWorldPos - worldPos;

        m_Camera.Translate(delta);
    }

    if (inputs.IsHeld(Input::Action::CAMERA_PAN_UP))
    {
        float panSpeed = m_PanSpeed * GameConstants::DeltaTime_Real;
        m_Camera.Translate(0.0f, panSpeed);
    }

    if (inputs.IsHeld(Input::Action::CAMERA_PAN_DOWN))
    {
        float panSpeed = m_PanSpeed * GameConstants::DeltaTime_Real;
        m_Camera.Translate(0.0f, -panSpeed);
    }

    if (inputs.IsHeld(Input::Action::CAMERA_PAN_LEFT))
    {
        float panSpeed = m_PanSpeed * GameConstants::DeltaTime_Real;
        m_Camera.Translate(-panSpeed, 0.0f);
    }

    if (inputs.IsHeld(Input::Action::CAMERA_PAN_RIGHT))
    {
        float panSpeed = m_PanSpeed * GameConstants::DeltaTime_Real;
        m_Camera.Translate(panSpeed, 0.0f);
    }

    float zoomAmount = inputs.GetRange(Input::Range::CAMERA_ZOOM) * m_ZoomSpeed;
    m_Camera.Zoom(zoomAmount);
}