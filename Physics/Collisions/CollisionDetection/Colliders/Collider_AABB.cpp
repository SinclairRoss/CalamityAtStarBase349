#include "Collider_AABB.h"

#include <string>

#include "GameConstants\GameConstants.h"
#include "Core\Utils\ColourLibrary.h"

Collider_AABB::Collider_AABB(const Matrix4& parent, float width, float height, bool highlight, Colour colour) :
    Collider(parent, std::string("Misc_Highlight"), highlight, colour),
    m_HalfSize(width / 2, height / 2)
{
    m_Transform.SetScale_Local(width, height);
}

float Collider_AABB::Left() const
{
    float left = m_Transform.GetPosition().X - m_HalfSize.X;
    return left;
}

float Collider_AABB::Right() const
{
    float right = m_Transform.GetPosition().X + m_HalfSize.X;
    return right;
}

float Collider_AABB::Top() const
{
    float top = m_Transform.GetPosition().Y + m_HalfSize.Y;
    return top;
}

float Collider_AABB::Bottom() const
{
    float bottom = m_Transform.GetPosition().Y - m_HalfSize.Y;
    return bottom;
}

Vector2 Collider_AABB::GetHalfSize() const
{
    return m_HalfSize;
}