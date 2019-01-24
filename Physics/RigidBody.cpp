#include "RigidBody.h"

#include <math.h>

#include "Core\Physics\Collisions\ColliderRegister\InteractionBoundsRegister.h"
#include "Core/Physics/Collisions/ColliderRegister/RigidBodyRegister.h"
#include "GameConstants\GameConstants.h"

RigidBody::RigidBody(Matrix4& transform, Collider* collider, float mass, float bounciness) :
    m_Collider(collider),
    m_Velocity(),
    m_Mass_Inv(abs(mass) > 0.001f ? (1.0f / mass) : 0.0f),
    m_Bounciness(bounciness),
    m_Transform(&transform)
{
	RigidBodyRegister::RegisterObject(*this, m_Mass_Inv, m_Collider.get());
}

RigidBody::~RigidBody()
{
	RigidBodyRegister::DeregisterObject(*this, m_Mass_Inv);
}

RigidBody::RigidBody(RigidBody&& other) noexcept :
    m_Collider(std::move(other.m_Collider)),
    m_Velocity(std::move(other.m_Velocity)),
    m_Mass_Inv(std::move(other.m_Mass_Inv)),
    m_Bounciness(std::move(other.m_Bounciness)),
    m_Transform(std::move(other.m_Transform))
{
	RigidBodyRegister::RegisterObject(*this, m_Mass_Inv, m_Collider.get());
}

RigidBody& RigidBody::operator=(RigidBody&& other) noexcept
{
    if (this != &other)
    {
        m_Collider = std::move(other.m_Collider);
        m_Velocity = std::move(other.m_Velocity);
        m_Mass_Inv = std::move(other.m_Mass_Inv);
        m_Bounciness = std::move(other.m_Bounciness);
        m_Transform = std::move(other.m_Transform);

		RigidBodyRegister::RegisterObject(*this, m_Mass_Inv, m_Collider.get());
    }

    return *this;
}

void RigidBody::Update()
{
    m_Transform->Translate(m_Velocity * GameConstants::DeltaTime_Real);
}

void RigidBody::ApplyForce_Instant(const Vector2& direction, float magnitude) { ApplyForce(direction * magnitude); }
void RigidBody::ApplyForce_Instant(const Vector2& force)
{
    Vector2 acceleration = force * m_Mass_Inv;
    m_Velocity += acceleration;
}

void RigidBody::ApplyForce(const Vector2& direction, float magnitude) { ApplyForce(direction * magnitude); }
void RigidBody::ApplyForce(const Vector2& force)
{
    Vector2 acceleration = force * m_Mass_Inv;
    m_Velocity += acceleration * GameConstants::DeltaTime_Real;
}

void RigidBody::SetVelocity(const Vector2& direction, float speed) { SetVelocity(direction * speed); }
void RigidBody::SetVelocity(const Vector2& velocity)
{
    m_Velocity = velocity;
}

void RigidBody::Stop() { m_Velocity.X = 0; m_Velocity.Y = 0; }

void RigidBody::OnMoveOperation(Matrix4& transform)
{
    m_Transform = &transform;
    m_Collider->OnMoveOperation(*m_Transform);
}

const Vector2& RigidBody::GetVelocity() const { return m_Velocity; }
const Vector2 RigidBody::GetPosition() const { return m_Transform->GetPosition(); }
const float RigidBody::GetBounciness() const { return m_Bounciness; }
void RigidBody::Translate(const Vector2& vec) { m_Transform->Translate(vec); }

float RigidBody::GetMass_Inv() const { return m_Mass_Inv; };
const Collider* RigidBody::GetCollider() const { return m_Collider.get(); }
Collider* RigidBody::GetCollider() { return m_Collider.get(); }