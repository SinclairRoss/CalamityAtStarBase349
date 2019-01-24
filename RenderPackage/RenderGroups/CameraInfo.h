#pragma once

#include <array>

#include "Core\Math\Vector.h"

class CameraInfo
{
    public:
        CameraInfo();

        void SetPosition(const Vector2& position);
        const std::array<float, 3>& GetPosition() const;

        float GetZoom() const;
        void SetZoom(float zoom);

    private:
        std::array<float, 3> m_Position;
        float m_Zoom;
};
