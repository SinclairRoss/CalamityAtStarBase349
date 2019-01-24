// name: CharacterAction_Move
// date: 17/04/2018
// Note: A move action that can be assigned to a character

#pragma once

#include "CharacterMovement.h"

class CharacterMovement_Walk : public CharacterMovement
{
	public:
        CharacterMovement_Walk(RigidBody& rigidBody);
        ~CharacterMovement_Walk() = default;

        CharacterMovement_Walk(const CharacterMovement_Walk&) = default;
        CharacterMovement_Walk& operator=(const CharacterMovement_Walk&) = default;

        CharacterMovement_Walk(CharacterMovement_Walk&&) noexcept = default;
        CharacterMovement_Walk& operator=(CharacterMovement_Walk&&) noexcept = default;

		void ParseInput(float x, float y) override;

	private: 
		float m_WalkingSpeed;
};