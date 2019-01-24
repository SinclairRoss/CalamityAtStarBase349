#include "MapBound.h"

#include "Core\Physics\Collisions\CollisionDetection\Colliders\Collider_AABB.h"
#include "Core\Preprocessor\Preprocessor.h"

MapBound::MapBound(Vector2& position, Vector2& size) :
    m_Transform(),
    m_RigidBody(m_Transform, new Collider_AABB(m_Transform, size.X, size.Y, HIGHLIGHT_RIGIDBODY_STATIC, ColourLibrary::Highlight_RigidBody_Static), 0.0f, 0.0f)
{
    m_Transform.SetPosition(position);
}

MapBound::MapBound(MapBound&& other) noexcept :
    m_Transform(std::move(other.m_Transform)),
    m_RigidBody(std::move(other.m_RigidBody))
{
    m_RigidBody.OnMoveOperation(m_Transform);
}

MapBound& MapBound::operator=(MapBound&& other) noexcept
{
    if (this != &other)
    {
        m_Transform = std::move(other.m_Transform);
        m_RigidBody = std::move(other.m_RigidBody);

        m_RigidBody.OnMoveOperation(m_Transform);
    }

    return *this;
}