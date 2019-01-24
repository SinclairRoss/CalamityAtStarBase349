#pragma once

#include <vector>

#include "../ElementData.h"
#include "../Interactables/InteractableType.h"
#include "../Interactables/InteractableEffectType.h"
#include "Core\Math\Vector.h"

class ElementData_Interactable : public ElementData
{
    public:
        ElementData_Interactable(const std::string& name, InteractableType type, int textureID, float size_x, float size_y, float offset_X, float offset_Y, std::vector<Vector2> aiInteractionNodePos);

        InteractableType GetInteractableType() const;
        const std::vector<Vector2>& GetAIInteractionNodePositions() const;

    private:
        InteractableType m_InteractableType;
        std::vector<Vector2> m_AIInteractionNodePos;
};
