#include "MapElement_Floor.h"

MapElement_Floor::MapElement_Floor(const ElementData_Floor& data, const ElementInstanceData_Floor& instanceData, const Vector2& position, int rotationIndex) :
    MapElement(&data, position, rotationIndex)
{}

void MapElement_Floor::SetNeighbour(MapElement_Floor* neighbour, Cardinal::Direction dir)
{
    m_Neighbourhood.SetNeighbour(neighbour, dir);
}

Neighbourhood<MapElement_Floor>&  MapElement_Floor::GetNeighbourhood() { return m_Neighbourhood; }
const Neighbourhood<MapElement_Floor>&  MapElement_Floor::GetNeighbourhood() const { return m_Neighbourhood; }