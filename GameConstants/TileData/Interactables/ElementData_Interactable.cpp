#include "ElementData_Interactable.h"

ElementData_Interactable::ElementData_Interactable(const std::string& name, InteractableType type, int textureID, float size_x, float size_y, float offset_x, float offset_y, std::vector<Vector2> aiInteractionNodes) :
    ElementData(name, textureID, size_x, size_y, offset_x, offset_y),
    m_InteractableType(type),
    m_AIInteractionNodePos(aiInteractionNodes)
{}

InteractableType ElementData_Interactable::GetInteractableType() const { return m_InteractableType; }
const std::vector<Vector2>& ElementData_Interactable::GetAIInteractionNodePositions() const { return m_AIInteractionNodePos; }