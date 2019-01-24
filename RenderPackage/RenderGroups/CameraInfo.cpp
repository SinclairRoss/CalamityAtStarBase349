#include "CameraInfo.h"

CameraInfo::CameraInfo() :
    m_Position{0.0f, 0.0f, 1.0f}
{}

void CameraInfo::SetPosition(const Vector2& position)
{
    m_Position[0] = position.X;
    m_Position[1] = position.Y;
}

const std::array<float, 3>& CameraInfo::GetPosition() const
{
    return m_Position;
}

float CameraInfo::GetZoom() const
{
    return m_Zoom;
}

void CameraInfo::SetZoom(float zoom)
{
    m_Zoom = zoom;
}