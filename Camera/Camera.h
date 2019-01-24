#pragma once

#include "glm/glm.hpp"

#include "Core\Math\Vector.h"
#include "Core\Math\Matrix4.h"

class Camera
{
public:
    Camera();

    Camera& operator=(const Camera& other);

    void SetPosition(float x, float y);
    void SetPosition(const Vector2& vec);
    void Translate(float x, float y);
    void Translate(const Vector2& vec);

    void SetZoom(float zoom);
    void Zoom(float zoom);

    void TrackTransform(const Matrix4* trans);

    Vector2 ScreenToWorldCoords(const Vector2& coords) const;
    Vector2 ScreenToWorldCoords(float x, float y) const;

    glm::mat4 CalculateViewProjectionMatrix() const;

private:
    const float ZOOM_MIN;
    const float ZOOM_MAX;

    Matrix4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;

    float m_Zoom;

    const Matrix4* m_TrackedTransform;
};