#include "Collider_Sphere.h"

Collider_Sphere::Collider_Sphere(Matrix4& parent, float radius, bool highlight, Colour colour) :
    Collider(parent, std::string("Misc_Highlight_Circle"), highlight, colour),
    m_Radius(radius),
    m_RadiusSqr(radius*radius)
{
    float circumference = radius * 2;
    m_Transform.SetScale_Local(circumference, circumference);
}

float Collider_Sphere::Radius() const
{
    return m_Radius;
}

float Collider_Sphere::Radius_Sqr() const
{
    return m_RadiusSqr;
}