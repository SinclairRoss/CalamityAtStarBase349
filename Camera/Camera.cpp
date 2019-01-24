#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core\Math\MathsHelper.h"
#include "GameConstants\GameConstants.h"

Camera::Camera() :
    ZOOM_MIN(0.03f),
    ZOOM_MAX(1.0f),
    m_ViewMatrix(),
    m_ProjectionMatrix(),
    m_Zoom(ZOOM_MIN),
    m_TrackedTransform(nullptr)
{
    m_ViewMatrix.SetPosition_Z(10.0f);

    SetPosition(1, 1);
    SetZoom(ZOOM_MIN);
}

Camera& Camera::operator=(const Camera& other)
{
    if (this != &other)
    {
        m_ViewMatrix = other.m_ViewMatrix;
        m_ProjectionMatrix = other.m_ProjectionMatrix;

        m_Zoom = other.m_Zoom;
        m_TrackedTransform = other.m_TrackedTransform;
    }

    return *this;
}

void Camera::SetPosition(float x, float y)
{
    m_ViewMatrix.SetPosition(x, y);
}

void Camera::SetPosition(const Vector2& vec)
{
    m_ViewMatrix.SetPosition(vec.X, vec.Y);
}

void Camera::Translate(float x, float y)
{
    m_ViewMatrix.Translate(x, y);
}

void Camera::Translate(const Vector2& vec)
{
    m_ViewMatrix.Translate(vec.X, vec.Y);
}

void Camera::SetZoom(float zoom)
{
    m_Zoom = MathsHelper::Clamp(zoom, ZOOM_MIN, ZOOM_MAX);

    float scale = 1.0f / m_Zoom;
    float scaledRatio = GameConstants::Window.AspectRatio() * scale;

    m_ProjectionMatrix = glm::ortho(-scaledRatio, scaledRatio, -scale, scale, 0.0f, 20.0f);
}

void Camera::Zoom(float zoom)
{
    SetZoom(m_Zoom + zoom);
}

Vector2 Camera::ScreenToWorldCoords(const Vector2& coords) const
{
    return ScreenToWorldCoords(coords.X, coords.Y);
}

Vector2 Camera::ScreenToWorldCoords(float x, float y) const
{
    glm::mat4 vpMatrix = CalculateViewProjectionMatrix();
    glm::mat4 vpMatrix_Inverse = glm::inverse(vpMatrix);

    x = MathsHelper::SignedNormalise(x, 0.0f, static_cast<float>(GameConstants::Window.ScreenWidth()));
    y = -MathsHelper::SignedNormalise(y, 0.0f, static_cast<float>(GameConstants::Window.ScreenHeight()));
    glm::vec4 screenPos(x, y, 0.0f, 1.0f);

    glm::vec4 worldPos = vpMatrix_Inverse * screenPos;
    float w = worldPos.w;
    worldPos /= w;

    return Vector2(worldPos.x, worldPos.y);
}

glm::mat4 Camera::CalculateViewProjectionMatrix() const
{
    return m_ProjectionMatrix * m_ViewMatrix.ResolveParents().AsGlmLookAt();
}

void Camera::TrackTransform(const Matrix4* trans)
{
    m_ViewMatrix.SetParent(trans);
}