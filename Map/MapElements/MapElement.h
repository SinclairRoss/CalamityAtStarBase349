#pragma once

#include <vector>

#include "Core\Renderables\Sprite.h"
#include "GameConstants\TileData\StaticElements\ElementData_Static.h"
#include "Core\Physics\Collisions\CollisionDetection\Colliders\Collider_AABB.h"
#include "Core\Utils\CardinalDirection.h"


class MapElement
{
    public:
        MapElement(const ElementData* data, const Vector2& position, int rotationIndex, bool showCollider = false);
        virtual ~MapElement() = default;
        MapElement(const MapElement&) = delete;
        MapElement& operator=(const MapElement&) = delete;
        MapElement(MapElement&& other) noexcept;
        MapElement& operator=(MapElement&& other) noexcept;

        Sprite& GetSprite();
        const Sprite& GetSprite() const;
        const std::string& GetElementDataName() const;
        const Vector2 GetPosition() const;
        const Collider_AABB& GetCollisionRect() const;
        const Matrix4& GetTransform() const;
        Matrix4& GetTransform();
        int GetRotationIndex() const;

        void SetZDepth(float z);

    private:
        std::string m_ElementDataName;

        Matrix4 m_Transform;
        Sprite m_Sprite;
        Collider_AABB m_CollisionRect; // Can this be removed?
        int m_RotationIndex; 
};

