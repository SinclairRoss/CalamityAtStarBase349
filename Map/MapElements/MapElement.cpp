#include "MapElement.h"

#include "Core\Math\MathsHelper.h"
#include "GameConstants\GameConstants.h"
#include "Core\RenderPackage\DisplayLayer.h"

#include "Core\Physics\Collisions\ColliderRegister\InteractionBoundsRegister.h"

MapElement::MapElement(const ElementData* data, const Vector2& position, int rotationIndex, bool showCollider) :
    m_ElementDataName(data->GetName()),
    m_Transform(),
    m_Sprite(DisplayLayer::FLOOR, data->GetTextureID(), data->GetPositionOffset().X, data->GetPositionOffset().Y),
    m_CollisionRect(m_Transform, 1.0f, 1.0f, showCollider),
    m_RotationIndex(rotationIndex)
{
    m_Transform.SetPosition(position);

    m_Sprite.SetParentTransform(&m_Transform);
    m_Sprite.SetScale(data->GetSize());
}

MapElement::MapElement(MapElement&& other) noexcept :
    m_ElementDataName(std::move(other.m_ElementDataName)),
    m_Transform(std::move(other.m_Transform)),
    m_Sprite(std::move(other.m_Sprite)),
    m_CollisionRect(std::move(other.m_CollisionRect)),
    m_RotationIndex(std::move(other.m_RotationIndex))
{
    m_Sprite.SetParentTransform(&m_Transform);
    m_CollisionRect.OnMoveOperation(m_Transform);
}

MapElement& MapElement::operator=(MapElement&& other) noexcept
{
    if (this != &other)
    {
        m_ElementDataName = std::move(other.m_ElementDataName);
        m_Transform = std::move(other.m_Transform);
        m_Sprite = std::move(other.m_Sprite);
        m_CollisionRect = std::move(other.m_CollisionRect);
        m_RotationIndex = std::move(other.m_RotationIndex);

        m_Sprite.SetParentTransform(&m_Transform);
        m_CollisionRect.OnMoveOperation(m_Transform);
    }

    return *this;
}
// Getters
Sprite& MapElement::GetSprite() { return m_Sprite; }
const Sprite& MapElement::GetSprite() const { return m_Sprite; }
const Collider_AABB& MapElement::GetCollisionRect() const { return m_CollisionRect; }
const Matrix4& MapElement::GetTransform() const { return m_Transform; }
Matrix4& MapElement::GetTransform() { return m_Transform; }
const Vector2 MapElement::GetPosition() const { return m_Transform.GetPosition_Local(); }
const std::string& MapElement::GetElementDataName() const { return m_ElementDataName; }
int MapElement::GetRotationIndex() const { return m_RotationIndex; }

// Setters
void MapElement::SetZDepth(float z) { m_Sprite.SetZDepth(z); }
