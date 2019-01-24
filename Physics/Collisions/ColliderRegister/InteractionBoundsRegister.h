#pragma once

#include <functional>
#include <utility>

#include <typeinfo>

#include "Utils\ColliderRegisterSet.h"

class Interactable;

namespace InteractionBoundsRegister
{
    namespace Internal
    {
        extern ColliderRegisterSet<Interactable> Register_Interactable;
        
        template<typename T>
        ColliderRegisterSet<T>& GetRegister() {};

        extern template
        ColliderRegisterSet<Interactable>& GetRegister<Interactable>();
    }

    template<typename T>
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
        Internal::GetRegister<T>().RegisterObject(&object, &collider);
    }

    template<typename T>
    void RegisterObject(T& object, const Collider_Sphere& collider)
    {
        Internal::GetRegister<T>().RegisterObject(&object, &collider);
    }

    template<typename T>
    void DeregisterObject(T& object)
    {
        Internal::GetRegister<T>().DeregisterObject(&object);
    }

    template<typename T>
    void Foreach(const std::function<void(T* obj)>& func)
    {
        Internal::GetRegister<T>().Foreach(func);
    }

    template<typename T>
    std::vector<CollisionReport<T>> DetectCollisions(T& object, const Collider* collider)
    {
        return Internal::GetRegister<T>().DetectCollisions(object, collider);
    }

    template<typename T>
    std::vector<CollisionReport<T>> DetectCollisions(T& object, const Collider_AABB& collider)
    {
        return Internal::GetRegister<T>().DetectCollisions<Collider_AABB>(object, collider);
    }

    template<typename T>
    std::vector<CollisionReport<T>> DetectCollisions(T& object, const Collider_Sphere& collider)
    {
        return Internal::GetRegister<T>().DetectCollisions<Collider_Sphere>(object, collider);
    }

    template<typename T>
    std::vector<T*> DetectCollisions_Simple(const Collider* collider)
    {
        return Internal::GetRegister<T>().DetectCollisions_Simple(collider);
    }

    template<typename T>
    std::vector<T*> DetectCollisions_Simple(const Collider_AABB& collider)
    {
        return Internal::GetRegister<T>().DetectCollisions_Simple<Collider_AABB>(collider);
    }

    template<typename T>
    std::vector<T*> DetectCollisions_Simple(const Collider_Sphere& collider)
    {
        return Internal::GetRegister<T>().DetectCollisions_Simple<Collider_Sphere>(collider);
    }
}
