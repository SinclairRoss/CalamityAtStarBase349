#include "UIElement.h"

UIElement::UIElement(float x, float y) :
    m_Transform()
{
    m_Transform.SetPosition(x, y);
}

UIElement::~UIElement()
{}

UIElement::UIElement(UIElement&& other) noexcept :
    m_Transform(std::move(other.m_Transform))
{}

UIElement& UIElement::operator=(UIElement&& other) noexcept
{
    if (this != &other)
    {
        m_Transform = std::move(other.m_Transform);
    }

    return *this;
}

const Matrix4& UIElement::GetTransform() const { return m_Transform; }