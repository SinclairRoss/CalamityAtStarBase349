#pragma once

#include "Core\Math\Matrix4.h"

class UIElement
{
    public:
        UIElement(float x, float y);
        virtual ~UIElement();

        UIElement(const UIElement&) = delete;
        UIElement& operator=(const UIElement&) = delete;

        UIElement(UIElement&&) noexcept;
        UIElement& operator=(UIElement&&) noexcept;

        const Matrix4& GetTransform() const;

    private:
        Matrix4 m_Transform;

};