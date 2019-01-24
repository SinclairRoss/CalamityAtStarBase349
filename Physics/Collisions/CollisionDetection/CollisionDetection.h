#pragma once

#include <math.h>
#include <memory>

#include "Colliders\Collider_AABB.h"
#include "Colliders\Collider_Sphere.h"

#include "Core\Math\MathsHelper.h"

#include "CollisionReport.h"

namespace CollisionDetection
{
    extern bool CheckCollision_Simple(const Vector2& point, const Collider_AABB& aabb);
    extern bool CheckCollision_Simple(const Vector2& point, const Collider_Sphere& sphere);
    extern bool CheckCollision_Simple(const Collider_AABB& a, const Collider_AABB& b);
    extern bool CheckCollision_Simple(const Collider_Sphere& a, const Collider_Sphere& b);
    extern bool CheckCollision_Simple(const Collider_Sphere& sphere, const Collider_AABB& aabb);
    extern bool CheckCollision_Simple(const Collider_AABB& aabb, const Collider_Sphere& sphere);

    template<typename T> extern CollisionReport<T> CheckCollision(T& objectA, const Collider* collA, T& objectB, const Collider* collB)
    {
        Collider_Sphere* s1 = dynamic_cast<Collider_Sphere*>(collA);
        Collider_Sphere* s2 = dynamic_cast<Collider_Sphere*>(collB);

        Collider_AABB* b1 = dynamic_cast<Collider_AABB*>(collA);
        Collider_AABB* b2 = dynamic_cast<Collider_AABB*>(collA);

        if (s1 != nullptr)
        {
            if (s2 != nullptr)
            {
                CheckCollision(objectA, *s1, objectB, *s2);
            }
            else if (b2 != nullptr)
            {
                CheckCollision(objectA, *s1, objectB, *s2);
            }
        }
        else if (b1 != nullptr)
        {
            if (s2 != nullptr)
            {
                CheckCollision(objectA, *s1, objectB, *s2);
            }
            else if (b2 != nullptr)
            {
                CheckCollision(objectA, *s1, objectB, *s2);
            }
        }
    }

    // Point - AABB
    template <typename T>
    CollisionReport<T> CheckCollision(T& objectA, const Vector2& point, T& objectB, const Collider_AABB& aabb)
    {
        bool collisionDetected = false;
        float penetrationDepth = 0.0f;
        Vector2 collisionNorm;

        CollisionReport report = nullptr;
        if (
            point.X >= aabb.Left() &&
            point.X <= aabb.Right() &&
            point.Y >= aabb.Bottom() &&
            point.Y <= aabb.Top())
        {
            collisionDetected = true;
            // Figure out details here.
        }

        return CollisionReport<T>(collisionDetected, objectA, objectB, collisionNorm, penetrationDepth);
    }

    // Point - Sphere
    template<typename T>
    CollisionReport<T> CheckCollision(T& objectA, const Vector2& point, T& objectB, const Collider_Sphere& sphere)
    {
        bool collisionDetected = false;
        float penetrationDepth = 0.0f;
        Vector2 collisionNorm;

        Vector2 pos = sphere.GetPosition();
        Vector2 aTob = pos - point;
        float distSqr = toPoint.CalculateLength_Sqr();

        if (distSqr < sphere.Radius_Sqr())
        {
            collisionDetected = true;
            penetrationDepth = sphere.Radius() - aTob.CalculateLength();
            collisionNorm = aTob;
            collisionNorm.Normalise();
        }

        return CollisionReport<T>(collisionDetected, objectA, objectB, collisionNorm, penetrationDepth);
    }

    // AABB - AABB
    template<typename T>
    CollisionReport<T> CheckCollision(T& objectA, const Collider_AABB& a, T& objectB, const Collider_AABB& b)
    {
        bool collisionDetected = false;
        float penetrationDepth = 0.0f;
        Vector2 collisionNorm;

        if (&a != &b)
        {
           Vector2 pos_A = a.GetPosition();
           Vector2 pos_B = b.GetPosition();
           Vector2 halfSize_A = a.GetHalfSize();
           Vector2 halfSize_B = b.GetHalfSize();

            Vector2 aToB = pos_B - pos_A;

            float overlap_X = (halfSize_A.X + halfSize_B.X) - std::abs(aToB.X);
            if (overlap_X > 0)
            {
                float overlap_Y = (halfSize_A.Y + halfSize_B.Y) - std::abs(aToB.Y);
                if (overlap_Y > 0)
                {
                    collisionDetected = true;

                    if (overlap_X < overlap_Y)
                    {
                        collisionNorm = (aToB.X < 0) ? Vector2(-1, 0) : Vector2(1, 0);
                        penetrationDepth = overlap_X;                      
                    }
                    else
                    {
                        collisionNorm = (aToB.Y < 0) ? Vector2(0, -1) : Vector2(0, 1);
                        penetrationDepth = overlap_Y;
                    }
                }
            }
        }
        else
        {
            printf("Check collision with self");
        }

        return CollisionReport<T>(collisionDetected, objectA, objectB, collisionNorm, penetrationDepth);
    }

    // Sphere - Sphere
    template<typename T>
    CollisionReport<T> CheckCollision(T& objectA, const Collider_Sphere& a, T& objectB, const Collider_Sphere& b)
    {
        bool collisionDetected = false;
        float penetrationDepth = 0.0f;
        Vector2 collisionNorm;

        if (&a != &b)
        {
            Vector2 posA = a.GetPosition();
            Vector2 posB = b.GetPosition();

            Vector2 toOther = posB - posA;
            float distSqr = toOther.CalculateLength_Sqr();
            float RadiusSum = a.Radius() + b.Radius();

            if (distSqr < (RadiusSum * RadiusSum))
            {
                collisionDetected = true;
                penetrationDepth = (a.Radius() + b.Radius()) - toOther.CalculateLength();
                collisionNorm = toOther;
                collisionNorm.Normalise();
            }
        }
        else
        {
            printf("Check collision with self\n");
        }

        return CollisionReport<T>(collisionDetected, objectA, objectB, collisionNorm, penetrationDepth);
    }

    // AABB - Sphere
    template<typename T>
    CollisionReport<T> CheckCollision(T& objectA, const Collider_AABB& aabb, T& objectB, const Collider_Sphere& sphere)
    {
        bool collisionDetected = false;
        float penetrationDepth = 0.0f;
        Vector2 collisionNorm;

        Vector2 posA = aabb.GetPosition();
        Vector2 posB = sphere.GetPosition();
        Vector2 aabb_HalfSize = aabb.GetHalfSize();

        Vector2 toOther = posB - posA;
        Vector2 closestSide = Vector2(MathsHelper::Clamp(toOther.X, -aabb_HalfSize.X, aabb_HalfSize.X),
                                  MathsHelper::Clamp(toOther.Y, -aabb_HalfSize.Y, aabb_HalfSize.Y));

        bool sphereInside = CheckCollision_Simple(sphere.GetPosition(), aabb);
        if (sphereInside)
        {
            if (std::abs(toOther.X) > std::abs(toOther.Y))
            {
                closestSide.X = (closestSide.X > 0) ? aabb_HalfSize.X : -aabb_HalfSize.X;
            }
            else
            {
                closestSide.Y = (closestSide.Y > 0) ? aabb_HalfSize.Y : -aabb_HalfSize.Y;
            }
        }

        collisionNorm = toOther - closestSide;
        float toClosest_Sqr = collisionNorm.CalculateLength_Sqr();
        float radius_Sqr = sphere.Radius_Sqr();

        if (toClosest_Sqr < radius_Sqr || sphereInside)
        {
            if (sphereInside)
            {
                collisionNorm *= -1;
            }

            collisionDetected = true;
            penetrationDepth = sphere.Radius() - collisionNorm.CalculateLength();
            collisionNorm.Normalise();
        }

        return CollisionReport<T>(collisionDetected, objectA, objectB, collisionNorm, penetrationDepth);
    }

    // Sphere - AABB
    template<typename T>
    CollisionReport<T> CheckCollision(T& objectA, const Collider_Sphere& sphere, T& objectB, const Collider_AABB& aabb)
    {
        return CheckCollision(objectB, aabb, objectA, sphere);
    }
}