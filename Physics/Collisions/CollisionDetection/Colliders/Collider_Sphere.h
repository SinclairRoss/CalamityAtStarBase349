#pragma once

#include "Collider.h"

class Collider_Sphere : public Collider
{
    public:
        Collider_Sphere(Matrix4& parent, float radius, bool highlight = false, Colour colour = ColourLibrary::Highlight_InteractionBounds);

        float Radius() const;
        float Radius_Sqr() const;

    private:
        float m_Radius;
        float m_RadiusSqr;
};