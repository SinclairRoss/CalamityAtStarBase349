#include "CharacterMovement.h"

#include "Core\Physics\RigidBody.h"

CharacterMovement::CharacterMovement(RigidBody& rigidBody) :
    m_RigidBody(&rigidBody)
{}

void CharacterMovement::OnMoveOperation(RigidBody& rigidBody)
{
    m_RigidBody = &rigidBody;
}