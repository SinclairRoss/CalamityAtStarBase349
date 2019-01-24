#include "CharacterMovement_Walk.h"

#include "GameConstants\GameConstants.h"

CharacterMovement_Walk::CharacterMovement_Walk(RigidBody& rigidBody)
	: CharacterMovement(rigidBody),
    m_WalkingSpeed(2.0f)
{}

void CharacterMovement_Walk::ParseInput(float x, float y)
{
    Vector2 movementVector(x, y);

    movementVector.Normalise();
    m_RigidBody->SetVelocity(movementVector, m_WalkingSpeed);
}