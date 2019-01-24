#include "Character.h"

#include "Core\Utils\ColourLibrary.h"
#include "Core\Preprocessor\Preprocessor.h"

Character::Character(int textureID, Map& map, const Vector2& startingPos) :
    m_Transform(),
    m_RigidBody(m_Transform, new Collider_Sphere(m_Transform, 0.3f, HIGHLIGHT_RIGIDBODY_DYNAMIC, ColourLibrary::Highlight_RigidBody_Dynamic), 1.0f, 0.0f),
    m_Sprite(DisplayLayer::OBJECT, textureID),
    m_InteractableCollider(m_Transform, 0.1f, HIGHLIGHT_INTERACTABLE, ColourLibrary::Highlight_InteractionBounds),
    m_Map(&map),
    m_CharacterState(),
    m_InteractableSensor(&m_InteractableCollider, m_CharacterState),
    m_Movement_Walk(m_RigidBody),
    m_ActiveMovementBehaviour(&m_Movement_Walk),
    m_BespokeAction_Interact(m_InteractableSensor)
{
    m_Transform.SetPosition(startingPos);
    m_CharacterState.UpdatePosition(startingPos);

    m_Sprite.SetScale(1, 2);
    m_Sprite.Translate(0.0f, 1.0f);
    m_Sprite.SetParentTransform(&m_Transform);
}

Character::Character(Character&& other) noexcept :
    m_Transform(std::move(other.m_Transform)),
    m_RigidBody(std::move(other.m_RigidBody)),
    m_Sprite(std::move(other.m_Sprite)),
    m_InteractableCollider(std::move(other.m_InteractableCollider)),
    m_Map(std::move(other.m_Map)),
    m_CharacterState(std::move(other.m_CharacterState)),
    m_InteractableSensor(std::move(other.m_InteractableSensor)),
    m_Movement_Walk(std::move(other.m_Movement_Walk)),
    m_ActiveMovementBehaviour(std::move(other.m_ActiveMovementBehaviour)),
    m_BespokeAction_Interact(std::move(other.m_BespokeAction_Interact))
{
    m_Sprite.SetParentTransform(&m_Transform);
    m_InteractableCollider.OnMoveOperation(m_Transform);
    m_RigidBody.OnMoveOperation(m_Transform);
    m_Movement_Walk.OnMoveOperation(m_RigidBody);
    m_InteractableSensor.OnMoveOperation(&m_InteractableCollider, m_CharacterState);

    m_ActiveMovementBehaviour = &m_Movement_Walk;
}

Character& Character::operator=(Character&& other) noexcept
{
    if (this != &other)
    {
        m_Transform = std::move(other.m_Transform);
        m_RigidBody = std::move(other.m_RigidBody);
        m_Sprite = std::move(other.m_Sprite);
        m_InteractableCollider = std::move(other.m_InteractableCollider);
        m_Map = std::move(other.m_Map);
        m_CharacterState = std::move(other.m_CharacterState);
        m_InteractableSensor = std::move(other.m_InteractableSensor);
        m_Movement_Walk = std::move(other.m_Movement_Walk);
        m_ActiveMovementBehaviour = std::move(other.m_ActiveMovementBehaviour);
        m_BespokeAction_Interact = std::move(other.m_BespokeAction_Interact);
        
        m_Sprite.SetParentTransform(&m_Transform);
        m_InteractableCollider.OnMoveOperation(m_Transform);
        m_RigidBody.OnMoveOperation(m_Transform);
        m_Movement_Walk.OnMoveOperation(m_RigidBody);
        m_InteractableSensor.OnMoveOperation(&m_InteractableCollider, m_CharacterState);

        m_ActiveMovementBehaviour = &m_Movement_Walk;
    }

    return *this;
}

void Character::UpdateCharacterState()
{
    m_InteractableSensor.Update();
    m_CharacterState.UpdatePosition(m_Transform.GetPosition());
}

void Character::ParseInput(const Input::MappedInput& input)
{
    m_ActiveMovementBehaviour->ParseInput(input.GetRange(Input::Range::MOVE_X), input.GetRange(Input::Range::MOVE_Y));

    if (input.IsPressed(Input::Action::INTERACT))
    {
        m_BespokeAction_Interact.Interact();
    }
}

const MapElement_Floor* Character::GetStandingTile() const 
{ 
    Vector2 pos = m_Transform.GetPosition();
    MapElement_Floor* standingTile = m_Map->GetMapLayer(0).GetElementAt<MapElement_Floor>(pos);

    return standingTile;
}

MapElement_Floor* Character::GetStandingTile()
{ 
    MapElement_Floor* standingTile = const_cast<MapElement_Floor*>(static_cast<const Character&>(*this).GetStandingTile());
    return standingTile;
}

const Matrix4& Character::GetTransform() const { return m_Transform; }
const Vector2 Character::GetPosition() const { return m_Transform.GetPosition(); }

const CharacterState& Character::GetCharacterState() const { return m_CharacterState; }
CharacterMovement& Character::GetActiveMovementBehaviour() { return *m_ActiveMovementBehaviour; }