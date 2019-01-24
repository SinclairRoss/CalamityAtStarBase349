#pragma once

#include "Collider.h"

class Collider_AABB : public Collider
{
    public:
        Collider_AABB(const Matrix4& parent, float width, float height, bool highlight = false, Colour colour = ColourLibrary::White);

        float Left() const;
        float Right() const;
        float Top() const;
        float Bottom() const;

        Vector2 GetHalfSize() const;

    private:
        Vector2 m_HalfSize;
};
