#pragma once

#include "Core\Physics\RigidBody.h"
#include "Core\Math\Vector.h"
#include "Core\Math\Matrix4.h"

class MapBound
{
    public:
        MapBound(Vector2& position, Vector2& size);
        ~MapBound() = default;
        MapBound(const MapBound&) = delete;
        MapBound& operator=(const MapBound&) = delete;
        MapBound(MapBound&& other) noexcept;
        MapBound& operator=(MapBound&& other) noexcept;


    private:
        
        Matrix4 m_Transform;
        RigidBody m_RigidBody;

};