#include "Collider.h"

#include "GameConstants\GameConstants.h"
#include "Core\Utils\ColourLibrary.h"

Collider::Collider(const Matrix4& parent, std::string& highlight, bool highlightOn, Colour colour) :
    m_Transform(),
    m_Highlight(DisplayLayer::OBJECT, GameConstants::TextureData.GetIDWithName(highlight))
{
    m_Transform.SetParent(parent);

    m_Highlight.SetParentTransform(&m_Transform);
    m_Highlight.SetColour(colour);
    
    if (!highlightOn)
    {
        m_Highlight.Deregister();
    }
}

Collider::Collider(Collider&& other) noexcept :
    m_Transform(std::move(other.m_Transform)),
    m_Highlight(std::move(other.m_Highlight))
{
    m_Highlight.SetParentTransform(&m_Transform);
}

Collider& Collider::operator= (Collider&& other) noexcept
{
    if (this != &other)
    {
        m_Transform = std::move(other.m_Transform);
        m_Highlight = std::move(other.m_Highlight);

        m_Highlight.SetParentTransform(&m_Transform);
    }

    return *this;
}

void Collider::OnMoveOperation(const Matrix4* parent) { m_Transform.SetParent(parent); }
void Collider::OnMoveOperation(const Matrix4& parent) { m_Transform.SetParent(&parent); }
      
Matrix4& Collider::GetTransform() { return m_Transform; }
const Matrix4& Collider::GetTransform() const { return m_Transform; }
Vector2 Collider::GetPosition() const { return m_Transform.GetPosition(); }
