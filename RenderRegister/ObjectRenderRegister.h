#pragma once

#include <functional>

#include "Core\GenericRegister\GenericRegister.h"

class Sprite;
class UIElement_TextBox;

namespace ObjectRenderRegister
{
    namespace Internal
    {
        extern GenericRegister<Sprite> RenderRegister_Sprite;
        extern GenericRegister<UIElement_TextBox> RenderRegister_Text;

        template<typename T>
        GenericRegister<T>& GetRegister()
        {
            No specialisation for given type.
        };

        extern template
        GenericRegister<Sprite>& GetRegister<Sprite>();

        extern template
        GenericRegister<UIElement_TextBox>& GetRegister<UIElement_TextBox>();
    }

    template<typename T>
    void RegisterObject(T& object)
    {
        Internal::GetRegister<T>().RegisterObject(object);
    }

    template<typename T>
    void DeregisterObject(T& object)
    {
        Internal::GetRegister<T>().DeregisterObject(object);
    }

    template<typename T>
    void Replace(T& oldObj, T& newObj)
    {
        Internal::GetRegister<T>().Replace(oldObj, newObj);
    }

    template<typename T>
    void Foreach(const std::function<void(T* obj)>& func)
    {
        Internal::GetRegister<T>().Foreach(func);
    }
}
