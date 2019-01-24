#include "CollisionDetection.h"

#include <math.h>

namespace CollisionDetection
{
    bool CheckCollision_Simple(const Vector2& point, const Collider_AABB& aabb)
    {
        bool collision =
            point.X >= aabb.Left() &&
            point.X <= aabb.Right() &&
            point.Y >= aabb.Bottom() &&
            point.Y <= aabb.Top();

        return collision;
    }

    bool CheckCollision_Simple(const Vector2& point, const Collider_Sphere& sphere)
    {
        Vector2 pos = sphere.GetPosition();
        Vector2 toPoint = point - pos;
        float distSqr = toPoint.CalculateLength_Sqr();

        bool collision = distSqr < sphere.Radius_Sqr();
        return collision;
    }

    bool CheckCollision_Simple(const Collider_AABB& a, const Collider_AABB& b)
    {
        bool collision = false;

        if (&a != &b)
        {
            float aR = a.Right();
            float aL = a.Left();
            float aT = a.Top();
            float aB = a.Bottom();

            float bR = b.Right();
            float bL = b.Left();
            float bT = b.Top();
            float bB = b.Bottom();

            collision = 
                aR > bL &&
                aL < bR &&
                aT > bB &&
                aB < bT;
        }
        
        return collision;
    }

    bool CheckCollision_Simple(const Collider_Sphere& a, const Collider_Sphere& b)
    {
        bool collision = false;

        if (&a != &b)
        {
            Vector2 posA = a.GetPosition();
            Vector2 posB = b.GetPosition();

            Vector2 toOther = posB - posA;
            float distSqr = toOther.CalculateLength_Sqr();
            float RadiusSum = a.Radius() + b.Radius();

            collision = distSqr < (RadiusSum * RadiusSum);
        }

        return collision;
    }

    bool CheckCollision_Simple(const Collider_Sphere& sphere, const Collider_AABB& aabb)
    {
        return CheckCollision_Simple(aabb, sphere);
    }

    bool CheckCollision_Simple(const Collider_AABB& aabb, const Collider_Sphere& sphere)
    {
        return false;
    }

    bool CheckCollision_Simple(const Collider_AABB& aabb, Vector2& rayStart, Vector2& rayEnd)
    {


        return false;
    }
}