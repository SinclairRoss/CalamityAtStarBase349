#pragma once

#include "../Map.h"
#include "Core\Math\Vector.h"

namespace MapUtils
{
	extern void GenerateBounds(Map& map);
    extern void CalculateFloorTileNeighbourhoods(Map& map);
    extern void GenerateNavMesh(Map& map);
}