// name: Character
// date: 17/04/2018
// Note: A character in the game controlled by a player

#pragma once

#include <memory>

#include "Core\Math\Matrix4.h"
#include "Core\Renderables\Sprite.h"
#include "Core\Physics\RigidBody.h"
#include "Core\Physics\Collisions\CollisionDetection\Colliders\Collider_Sphere.h"
#include "Core\Preprocessor\BoilerPlate.h"
#include "CharacterState\CharacterState.h"
#include "CharacterActions\Movement\CharacterMovement.h"
#include "CharacterActions\Movement\CharacterMovement_Walk.h"
#include "CharacterActions\Bespoke\BespokeAction_Interact.h"
#include "Sensors\InteractableSensor.h"
#include "GameObjects\Interactables\Interactable.h"
#include "Map\Map.h"

class Character
{
	public:
		Character(int textureID, Map& map, const Vector2& startingPos);
        Character(const Character&) = delete;
        Character& operator=(const Character&) = delete;
        Character(Character&& other) noexcept;
        Character& operator=(Character&& other) noexcept;

        void UpdateCharacterState();
        void ParseInput(const Input::MappedInput& input);

        const MapElement_Floor* GetStandingTile() const;
        MapElement_Floor* GetStandingTile();

        const Matrix4& GetTransform() const;
        const Vector2 GetPosition() const;

        const CharacterState& GetCharacterState() const;
        CharacterMovement& GetActiveMovementBehaviour();

	private:
        
        Matrix4 m_Transform;
        RigidBody m_RigidBody;

		Sprite m_Sprite;
        Collider_Sphere m_InteractableCollider;

        Map* m_Map;

        CharacterState m_CharacterState;
        
        // Sensors
        InteractableSensor m_InteractableSensor;

        // Actions
        CharacterMovement_Walk m_Movement_Walk;
        CharacterMovement* m_ActiveMovementBehaviour;

        BespokeAction_Interact m_BespokeAction_Interact;
};
