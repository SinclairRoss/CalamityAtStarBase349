#pragma once

#include "ObjectRenderRegister.h"

namespace ObjectRenderRegister
{
    namespace Internal
    {
        GenericRegister<Sprite> RenderRegister_Sprite;
        GenericRegister<UIElement_TextBox> RenderRegister_Text;

        template<>
        GenericRegister<Sprite>& GetRegister<Sprite>()
        {
            return RenderRegister_Sprite;
        }

        template<>
        GenericRegister<UIElement_TextBox>& GetRegister<UIElement_TextBox>()
        {
            return RenderRegister_Text;
        }
    }
}