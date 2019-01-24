#include "Map.h"

#include <cmath>

#include "GameConstants\GameConstants.h"
#include "Core\Renderables\Sprite.h"

Map::Map(int levelCount) :
    m_MapLevels(),
    m_AINodeRegister()
{
    m_MapLevels.reserve(levelCount);

    for (int i = 0; i < levelCount; ++i)
    {
        m_MapLevels.emplace_back(i);
    }
}

const MapLayer& Map::GetMapLayer(int index) const
{
    return m_MapLevels.at(index);
}

MapLayer& Map::GetMapLayer(int index)
{
    return m_MapLevels.at(index);
}

void Map::AddNewLevel()
{
    int newLevelIndex = m_MapLevels.size();

    m_MapLevels.reserve(newLevelIndex+1);
    m_MapLevels.emplace_back(newLevelIndex);
}

void Map::ForeachLevel(std::function<void(const MapLayer&)> func) const
{
    for (const MapLayer& layer : m_MapLevels)
    {
        func(layer);
    }
}
void Map::ForeachLevel(std::function<void(MapLayer&)> func)
{
    for (MapLayer& layer : m_MapLevels)
    {
        func(layer);
    }
}

int Map::GetLevelCount() const
{
    int levelCount = m_MapLevels.size();
    return levelCount;
}