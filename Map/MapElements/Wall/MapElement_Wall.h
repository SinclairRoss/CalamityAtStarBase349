#pragma once

#include "../MapElement.h"

#include "GameConstants\TileData\Wall\ElementData_Wall.h"
#include "GameConstants\TileData\Wall\ElementInstanceData_Wall.h"

class MapElement_Wall : public MapElement
{
    public:
        MapElement_Wall(const ElementData_Wall& data, const ElementInstanceData_Wall& instanceData, const Vector2& position, int rotationIndex);

    private:
};
