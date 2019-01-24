#pragma once

#include <memory>

#include "..\MapElement.h"
#include "GameConstants\TileData\Floor\ElementData_Floor.h"
#include "GameConstants\TileData\Floor\ElementInstanceData_Floor.h"
#include "Core\Physics\RigidBody.h"

#include "../../Utils/Neighbourhood.h"

class MapElement_Floor : public MapElement
{
    public:
        MapElement_Floor(const ElementData_Floor& data, const ElementInstanceData_Floor& instanceData, const Vector2& position, int rotationIndex);
        ~MapElement_Floor() = default;

        MapElement_Floor(const MapElement_Floor&) = delete;
        MapElement_Floor& operator=(const MapElement_Floor&) = delete;
        MapElement_Floor(MapElement_Floor&& other) noexcept = default;
        MapElement_Floor& operator=(MapElement_Floor&& other) noexcept = default;
        
        void SetNeighbour(MapElement_Floor* neighbour, Cardinal::Direction dir);
        
        const Neighbourhood<MapElement_Floor>& GetNeighbourhood() const;
        Neighbourhood<MapElement_Floor>& GetNeighbourhood();

    private:

        Neighbourhood<MapElement_Floor> m_Neighbourhood;


};
