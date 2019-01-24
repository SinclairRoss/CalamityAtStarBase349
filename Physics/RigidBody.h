#pragma once

#include <memory>

#include "Core\Physics\Collisions\CollisionDetection\Colliders\Collider.h"
#include "Core\Physics\Collisions\CollisionDetection\CollisionReport.h"

class RigidBody
{
    public:
        RigidBody(Matrix4& transform, Collider* collider, float mass, float bounciness);
        ~RigidBody();

        RigidBody(const RigidBody&) = default;
        RigidBody& operator=(const RigidBody&) = default;

        RigidBody(RigidBody&& other) noexcept;
        RigidBody& operator= (RigidBody&& other) noexcept;

        void OnMoveOperation(Matrix4& transform);

        void Update();
        
        void ApplyForce_Instant(const Vector2& direction, float magnitude);
        void ApplyForce_Instant(const Vector2& force);

        void ApplyForce(const Vector2& direction, float magnitude);
        void ApplyForce(const Vector2& force);

        void SetVelocity(const Vector2& direction, float speed);
        void SetVelocity(const Vector2& velocity);

        void Translate(const Vector2& vec);

        void Stop();

        const Vector2& GetVelocity() const;
        const Vector2 GetPosition() const;
        const float GetBounciness() const;

        float GetMass_Inv() const;
        const Collider* GetCollider() const;
        Collider* GetCollider();

    private:
        std::unique_ptr<Collider> m_Collider;

        Vector2 m_Velocity;
        float m_Mass_Inv;
        float m_Bounciness;

        Matrix4* m_Transform;
};
