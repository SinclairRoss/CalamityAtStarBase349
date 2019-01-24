#pragma once

#include <vector>
#include "Core\Math\Vector.h"

template <typename T>
class CollisionReport
{
    public:
        CollisionReport(bool collisionDetected, T& objectA, T& objectB, const Vector2& normal, float penetrationDepth) :
            m_CollisionDetected(collisionDetected),
            m_ObjectA(&objectA),
            m_ObjectB(&objectB),
            m_Normal(normal),
            m_PenetrationDepth(penetrationDepth)
        {}

        bool CollisionDetected() const { return m_CollisionDetected; }

        const Vector2 GetNormal() const { return m_Normal; }
        float GetPenetrationDepth() const { return m_PenetrationDepth; }

        T* const GetObjectA() const { return m_ObjectA; }
        T* const GetObjectB() const { return m_ObjectB; }

    private:

        bool m_CollisionDetected;

        T* m_ObjectA;
        T* m_ObjectB;

        Vector2 m_Normal;
        float m_PenetrationDepth;


};