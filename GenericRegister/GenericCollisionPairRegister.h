#pragma once


template<typename T>
class GenericCollisionPairRegister
{
    public:
        void RegisterObject(T& object, Collider* collider)
        {
            if (Collider_Sphere* s = dynamic_cast<Collider_Sphere*>(collider))
            {
                RegisterObject<T>(object, *s);
            }
            else if (Collider_AABB* b = dynamic_cast<Collider_AABB*>(collider))
            {
                RegisterObject<T>(object, *b);
            }
        }

        template<typename T>
        void RegisterObject(T& object, const Collider_AABB& collider)
        {
            m_Register.RegisterObject(&object, &collider);
        }

        template<typename T>
        void RegisterObject(T& object, const Collider_Sphere& collider)
        {
            m_Register.RegisterObject(&object, &collider);
        }

        template<typename T>
        void DeregisterObject(T& object)
        {
            m_Register.DeregisterObject(&object);
        }

        template<typename T>
        void Foreach(const std::function<void(T* obj)>& func)
        {
            m_Register.Foreach(func);
        }

        std::vector<CollisionReport<T>> DetectCollisions(T& object, const Collider* collider)
        {
            return m_Register.DetectCollisions(object, collider);
        }

        std::vector<CollisionReport<T>> DetectCollisions(T& object, const Collider_AABB& collider)
        {
            return m_Register.DetectCollisions<Collider_AABB>(object, collider);
        }

        std::vector<CollisionReport<T>> DetectCollisions(T& object, const Collider_Sphere& collider)
        {
            return m_Register.DetectCollisions<Collider_Sphere>(object, collider);
        }

        std::vector<T*> DetectCollisions_Simple(const Collider_AABB& collider)
        {
            return m_Register.DetectCollisions_Simple<Collider_AABB>(collider);
        }

        std::vector<T*> DetectCollisions_Simple(const Collider_Sphere& collider)
        {
            return m_Register.DetectCollisions_Simple<Collider_Sphere>(collider);
        }

    private:
        extern RegisterSet<T> m_Register;
};