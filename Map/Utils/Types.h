#pragma once

#include <memory>

#include "Core\Utils\Vector2D.h"
#include "Map\MapElements\Floor\MapElement_Floor.h"
#include "Algorithms\AStar\AStarNode.h"

using NavMesh = Vector2D<std::unique_ptr<AStarNode<MapElement_Floor>>>;
