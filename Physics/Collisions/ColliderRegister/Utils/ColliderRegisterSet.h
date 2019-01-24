#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#include "../../CollisionDetection/Colliders/Collider_AABB.h"
#include "../../CollisionDetection/Colliders/Collider_Sphere.h"
#include "../../CollisionDetection/CollisionDetection.h"

template <typename T>
class ColliderRegisterSet
{
    private:
        using Pair_AABB = std::pair<T*, const Collider_AABB*>;
        using Pair_Sphere = std::pair<T*, const Collider_Sphere*>;

        template<typename T> struct ColliderToPair {};
        template<> struct ColliderToPair<Collider_AABB> { using Type = Pair_AABB; };
        template<> struct ColliderToPair<Collider_Sphere> { using Type = Pair_Sphere; };

    public:
        ColliderRegisterSet() = default;
        ~ColliderRegisterSet() = default;
        ColliderRegisterSet(const ColliderRegisterSet&) = delete;
        ColliderRegisterSet& operator=(const ColliderRegisterSet&) = delete;
        ColliderRegisterSet(ColliderRegisterSet&&) = delete;
        ColliderRegisterSet& operator=(ColliderRegisterSet&&) = delete;

        template<typename Collider>
        void RegisterObject(T* object, const Collider* collider)
        {
            if (!IsCurrentlyRegistered(*object))
            {
                using Pair = ColliderToPair<Collider>::Type;
                Pair pair(object, collider);
                GetSet<Pair>().emplace_back(std::move(pair));
            }
            else
            {
                printf("Attempting to re-register collider\n");
            }
        }

        void DeregisterObject(const T* object)
        {
            m_AABB.erase(std::remove_if(m_AABB.begin(), m_AABB.end(), [object](const Pair_AABB& pair) { return pair.first == object; }), m_AABB.end());
            m_Sphere.erase(std::remove_if(m_Sphere.begin(), m_Sphere.end(), [object](const Pair_Sphere& pair) { return pair.first == object; }), m_Sphere.end());
        }

        std::vector<CollisionReport<T>> DetectCollisions(T& object, const Collider* collider)
        {
            std::vector<CollisionReport<T>> collisions;

            if (const Collider_AABB* b = dynamic_cast<const Collider_AABB*>(collider))
            {
                collisions = DetectCollisions<Collider_AABB>(object, *b);
            }
            else if (const Collider_Sphere* s = dynamic_cast<const Collider_Sphere*>(collider))
            {
                collisions = DetectCollisions<Collider_Sphere>(object, *s);
            }

            return collisions;
        }

        template<typename ColliderT>
        std::vector<CollisionReport<T>> DetectCollisions(T& object, const ColliderT& collider)
        {
            static_assert(std::is_base_of<Collider, ColliderT>::value, "ColliderT must inherit from Collider");

            std::vector<CollisionReport<T>> collisions;

            for (Pair_AABB& pair : m_AABB)
            {
                CollisionReport<T> report = CollisionDetection::CheckCollision<T>(object, collider, *pair.first, *pair.second);
                if (report.CollisionDetected())
                {
                    collisions.emplace_back(std::move(report));
                }
            }

            for (Pair_Sphere& pair : m_Sphere)
            {
                CollisionReport<T> report = CollisionDetection::CheckCollision<T>(object, collider, *pair.first, *pair.second);
                if (report.CollisionDetected())
                {
                    collisions.emplace_back(std::move(report));
                }
            }

            return collisions;
        }

        std::vector<T*> DetectCollisions_Simple(const Collider* collider)
        {
            std::vector<T*> collisions;

            if (const Collider_AABB* b = dynamic_cast<const Collider_AABB*>(collider))
            {
                collisions = DetectCollisions_Simple<Collider_AABB>(*b);
            }
            else if (const Collider_Sphere* s = dynamic_cast<const Collider_Sphere*>(collider))
            {
                collisions = DetectCollisions_Simple<Collider_Sphere>(*s);
            }

            return collisions;
        }

        template<typename ColliderT>
        std::vector<T*> DetectCollisions_Simple(const ColliderT& collider)
        {
            static_assert(std::is_base_of<Collider, ColliderT>::value, "ColliderT must inherit from Collider");

            std::vector<T*> collisions;

            for (Pair_AABB& pair : m_AABB)
            {
                if (CollisionDetection::CheckCollision_Simple(*pair.second, collider))
                {
                    collisions.push_back(pair.first);
                }
            }

            for (Pair_Sphere& pair : m_Sphere)
            {
                if (CollisionDetection::CheckCollision_Simple(*pair.second, collider))
                {
                    collisions.push_back(pair.first);
                }
            }

            return collisions;
        }



        template<typename set> std::vector<set>& GetSet() {}
        template<> std::vector<Pair_AABB>& GetSet<Pair_AABB>() { return m_AABB; }
        template<> std::vector<Pair_Sphere>& GetSet<Pair_Sphere>() { return m_Sphere; }

        template<typename set> const std::vector<set>& GetSet() const {}
        template<> const std::vector<Pair_AABB>& GetSet<Pair_AABB>() const { return m_AABB; }
        template<> const std::vector<Pair_Sphere>& GetSet<Pair_Sphere>() const { return m_Sphere; }

    private:

        bool IsCurrentlyRegistered(const T& obj) const
        {
            bool isRegistered = (std::find_if(m_AABB.begin(), m_AABB.end(), [&](const Pair_AABB& pair) { return pair.first == &obj; }) != m_AABB.end()) ||
                                (std::find_if(m_Sphere.begin(), m_Sphere.end(), [&](const Pair_Sphere& pair) { return pair.first == &obj; }) != m_Sphere.end());
            return isRegistered;
        }

        std::vector<Pair_AABB> m_AABB;
        std::vector<Pair_Sphere> m_Sphere;
};
