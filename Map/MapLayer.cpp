#include "MapLayer.h"

#include <array>
#include <cmath>

#include "Core\Physics\Collisions\CollisionDetection\CollisionDetection.h"
#include "Core\Utils\CardinalDirection.h"

#include "MapConstants.h"

MapLayer::MapLayer(int zDepth) :
    m_Elements_Floor(static_cast<float>(zDepth), MapConstants::MapSize_x, MapConstants::MapSize_y),
    m_Elements_Wall(static_cast<float>(zDepth), MapConstants::MapSize_x, MapConstants::MapSize_y),
    m_Elements_Interactable(static_cast<float>(zDepth), MapConstants::MapSize_x, MapConstants::MapSize_y),
	m_BoundsData()
{}

void MapLayer::SetNavMesh(NavMesh&& navMesh)
{
    m_NavMesh = std::move(navMesh);
}

void MapLayer::AddBounds(Vector2& position, Vector2& size)
{
    m_BoundsData.emplace_back(position, size);
}

AStarNode<MapElement_Floor>* MapLayer::GetPathingNode(const Vector2& position)
{
    uPoint point = Utils::WorldToGridCoords(position);
    AStarNode<MapElement_Floor>* node = m_NavMesh[point.X][point.Y].get();

    return node;
}