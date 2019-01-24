// name: CharacterAction
// date: 17/04/2018
// Note: The base class for action which can be assigned to a character

#pragma once

#include "Core/InputHandling/InputMapping/InputConstants.h"			// Action, Range
#include "Core/InputHandling/InputMapping/MappedInput.h"
#include "Core/Math/Matrix4.h"

#include "Core/Physics/RigidBody.h"

class CharacterMovement 
{
	public:
        CharacterMovement(RigidBody& rigidBody);
        virtual ~CharacterMovement() = default;

        CharacterMovement(const CharacterMovement&) = default;
        CharacterMovement& operator=(const CharacterMovement&) = default;

        CharacterMovement(CharacterMovement&&) noexcept = default;
        CharacterMovement& operator=(CharacterMovement&&) noexcept = default;

		virtual void ParseInput(float x, float y) = 0;

        void OnMoveOperation(RigidBody& rigidBody);

	protected:
        RigidBody* m_RigidBody;
};