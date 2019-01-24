#include "Sprite.h"

#include "Core\Utils\ColourLibrary.h"

Sprite::Sprite(DisplayLayer displayLayer, int textureID, float x, float y) :
    m_DisplayLayer(displayLayer),
    m_Transform(),
    m_Colour(),
    m_TextureID(textureID),
    m_IsRegistered(false)
{
    m_Transform.SetPosition(x, y);
    Register();
}

Sprite::~Sprite()
{
    Deregister();
}

Sprite::Sprite(Sprite&& other) noexcept :
    m_DisplayLayer(other.m_DisplayLayer),
    m_Transform(std::move(other.m_Transform)),
    m_Colour(std::move(other.m_Colour)),
    m_TextureID(other.m_TextureID),
    m_IsRegistered(false)
{
    if (other.m_IsRegistered)
    {
        Register();
    }
}

// Double check this actually works with regards to the object render register. Register()
Sprite& Sprite::operator=(Sprite&& other) noexcept
{
    if (this != &other)
    {
        m_DisplayLayer = other.m_DisplayLayer;
        m_Transform = std::move(other.m_Transform);
        m_Colour = std::move(other.m_Colour);
        m_TextureID = other.m_TextureID;
        m_IsRegistered = other.m_IsRegistered;

        if (!m_IsRegistered)
        {
            Deregister();
        }
    }

    return *this;
}

void Sprite::Register()
{
    ObjectRenderRegister::RegisterObject(*this);
    m_IsRegistered = true;
}

void Sprite::Deregister()
{
    ObjectRenderRegister::DeregisterObject(*this);
    m_IsRegistered = false;
}

void Sprite::Update()
{}

const Matrix4& Sprite::GetTransform() const
{
    return m_Transform;
}

int Sprite::GetTextureID() const
{
    return m_TextureID;
}

void Sprite::SetParentTransform(const Matrix4* parent) { m_Transform.SetParent(parent); }

void Sprite::SetPosition(int x, int y) { SetPosition(static_cast<float>(x), static_cast<float>(y)); }
void Sprite::SetPosition(const Vector2& pos) { SetPosition(pos.X, pos.Y); }
void Sprite::SetPosition(const Point& pos) { SetPosition(static_cast<float>(pos.X), static_cast<float>(pos.Y)); }
void Sprite::SetPosition(float x, float y) 
{ 
    m_Transform.SetPosition(x, y); 
}

void Sprite::Translate(int x, int y) { Translate(static_cast<float>(x), static_cast<float>(y)); }
void Sprite::Translate(const Vector2& deltaVec) { Translate(deltaVec.X, deltaVec.Y); }
void Sprite::Translate(const Point& pos) { Translate(static_cast<float>(pos.X), static_cast<float>(pos.Y)); }
void Sprite::Translate(float x, float y) 
{
    m_Transform.Translate(x, y);
}

void Sprite::SetZDepth(float z) { m_Transform.SetPosition_Z(z); }

void Sprite::SetScale(int x, int y) { SetScale(static_cast<float>(x), static_cast<float>(y)); }
void Sprite::SetScale(const Vector2& scale) { SetScale(scale.X, scale.Y); }
void Sprite::SetScale(const Point& scale) { SetScale(static_cast<float>(scale.X), static_cast<float>(scale.Y)); }
void Sprite::SetScale(float x, float y) 
{ 
    m_Transform.SetScale_Local(x, y); 
}

void Sprite::SetTextureID(int textureID) { m_TextureID = textureID; }
void Sprite::SetColour(const Colour& colour) { m_Colour.Set(colour); }
void Sprite::SetAlpha(float a) { m_Colour.A = a; }

void Sprite::SetRotation(float theta) { m_Transform.SetRotation(theta); }
void Sprite::Rotate(float theta) { m_Transform.Rotate(theta); }

const Colour& Sprite::GetColour() const { return m_Colour; }

DisplayLayer Sprite::GetDisplayLayer() const{ return m_DisplayLayer; }

Matrix4& Sprite::GetTransform() { return m_Transform; }

const Vector2 Sprite::GetPosition() const 
{
	return m_Transform.GetPosition_Local();
}
