#include "MapUtils.h"

#include <math.h>

#include "Map\MapElements\Floor\MapElement_Floor.h"
#include "GameConstants\TileData\Floor\ElementData_Floor.h"
#include "LevelEditor\Controller\SnapGrid.h"
#include "Core\Physics\RigidBody.h"
#include "Map\MapConstants.h"

#include "Core\Utils\CardinalDirection.h"
#include "Core\Utils\Utils.h"

#include "Types.h"

namespace MapUtils
{
	void GenerateBounds(Map& map)
	{
        SnapGrid snapGrid;

        map.ForeachLevel([&](MapLayer& layer)
        {
            MapElementCollection<MapElement_Floor>& collection = layer.GetElementList<MapElement_Floor>();
            uPoint size = collection.Size();

            std::vector<MapElement_Floor*> walls_North;
            std::vector<MapElement_Floor*> walls_South;
            std::vector<MapElement_Floor*> walls_East;
            std::vector<MapElement_Floor*> walls_West;

            for (unsigned int x = 0; x < size.X; ++x)
            {
                for (unsigned int y = 0; y < size.Y; ++y)
                {
                    MapElement_Floor* element = collection[x][y].get();
                    if (element != nullptr)
                    {
                        if (element->GetNeighbourhood().GetNeighbour(Cardinal::Direction::NORTH) == nullptr) { walls_North.push_back(element); }
                        if (element->GetNeighbourhood().GetNeighbour(Cardinal::Direction::SOUTH) == nullptr) { walls_South.push_back(element); }
                        if (element->GetNeighbourhood().GetNeighbour(Cardinal::Direction::EAST) == nullptr) { walls_East.push_back(element); }
                        if (element->GetNeighbourhood().GetNeighbour(Cardinal::Direction::WEST) == nullptr) { walls_West.push_back(element); }
                    }
                }
            }

            struct BoundSearchSettings
            {
                BoundSearchSettings(std::vector<MapElement_Floor*>& list, Cardinal::Direction exploreDir, Cardinal::Direction cornerCheckDir, float verticalOffset, float horizontalOffset, bool horizontalSearch) :
                    ActiveList(list),
                    ExploreDir(exploreDir),
                    CornerCheckDir(cornerCheckDir),
                    VerticalOffset(verticalOffset),
                    HorizontalOffset(horizontalOffset),
                    HorizontalSearch(horizontalSearch)
                {}

                std::vector<MapElement_Floor*>& ActiveList;
                Cardinal::Direction ExploreDir;
                Cardinal::Direction CornerCheckDir;
                float VerticalOffset;
                float HorizontalOffset;
                bool HorizontalSearch;
            };

            std::vector<BoundSearchSettings> searchParamList;
            searchParamList.reserve(4);
            searchParamList.emplace_back(walls_North, Cardinal::Direction::EAST, Cardinal::Direction::NORTH_EAST, 0.6f, 0.0f, true);
            searchParamList.emplace_back(walls_South, Cardinal::Direction::EAST, Cardinal::Direction::SOUTH_EAST, -0.6f, 0.0f, true);
            searchParamList.emplace_back(walls_East, Cardinal::Direction::NORTH, Cardinal::Direction::NORTH_EAST, 0.0f, 0.6f, false);
            searchParamList.emplace_back(walls_West, Cardinal::Direction::NORTH, Cardinal::Direction::NORTH_WEST, 0.0f, -0.6f, false);

            for (BoundSearchSettings& searchParam : searchParamList)
            {
                while (!searchParam.ActiveList.empty())
                {
                    const MapElement_Floor* startPoint = searchParam.ActiveList[0];
                    const MapElement_Floor* candidate = startPoint;
                    searchParam.ActiveList.erase(std::find(searchParam.ActiveList.begin(), searchParam.ActiveList.end(), candidate));

                    Vector2 bounds_Max = candidate->GetPosition();
                    Vector2 bounds_Min = bounds_Max;

                    if (searchParam.HorizontalSearch)
                    {
                        bounds_Max.X += 0.5f;
                        bounds_Min.X -= 0.5f;
                    }
                    else
                    {
                        bounds_Max.Y += 0.5f;
                        bounds_Min.Y -= 0.5f;
                    }

                    const MapElement_Floor* neighbour_Explore = candidate->GetNeighbourhood().GetNeighbour(searchParam.ExploreDir);
                    const MapElement_Floor* neighbour_CornerCheck = candidate->GetNeighbourhood().GetNeighbour(searchParam.CornerCheckDir);

                    while (neighbour_Explore != nullptr && neighbour_CornerCheck == nullptr)
                    {
                        if (searchParam.HorizontalSearch)
                        {
                            bounds_Max.X += 1.0f;
                        }
                        else
                        {
                            bounds_Max.Y += 1.0f;
                        }

                        candidate = neighbour_Explore;
                        searchParam.ActiveList.erase(std::find(searchParam.ActiveList.begin(), searchParam.ActiveList.end(), candidate));

                        neighbour_Explore = candidate->GetNeighbourhood().GetNeighbour(searchParam.ExploreDir);
                        neighbour_CornerCheck = candidate->GetNeighbourhood().GetNeighbour(searchParam.CornerCheckDir);
                    }

                    Vector2 boundSize;
                    Vector2 boundPosition;

                    if (searchParam.HorizontalSearch)
                    {
                        boundSize.X = bounds_Max.X - bounds_Min.X;
                        boundSize.Y = 0.2f;

                        boundPosition.X = bounds_Min.X + (boundSize.X / 2.0f);
                        boundPosition.Y = startPoint->GetPosition().Y + searchParam.VerticalOffset;
                    }
                    else
                    {
                        boundSize.X = 0.2f;
                        boundSize.Y = bounds_Max.Y - bounds_Min.Y;

                        boundPosition.X = startPoint->GetPosition().X + searchParam.HorizontalOffset;
                        boundPosition.Y = bounds_Min.Y + (boundSize.Y / 2.0f);
                    }

                    layer.AddBounds(boundPosition, boundSize);
                }
            }
        });
	}

    void CalculateFloorTileNeighbourhoods(Map& map)
    {
        map.ForeachLevel([&](MapLayer& layer)
        {
            MapElementCollection<MapElement_Floor>& collection = layer.GetElementList<MapElement_Floor>();
            uPoint size = collection.Size();

            for (unsigned int x = 0; x < size.X; ++x)
            {
                for (unsigned int y = 0; y < size.Y; ++y)
                {
                    MapElement_Floor* element = collection[x][y].get();
                    if (element != nullptr)
                    {
                        for (int i = 0; i < Cardinal::DirectionCount; ++i)
                        {
                            Cardinal::Direction dir = Cardinal::ToDirection(i);
                            Point candidateCoord = Cardinal::GetCardinalPoint(dir);
                            candidateCoord.X += x;
                            candidateCoord.Y += y;

                            if (static_cast<unsigned int>(candidateCoord.X) < size.X &&
                                static_cast<unsigned int>(candidateCoord.Y) < size.Y)
                            {
                                MapElement_Floor* candidate = collection[candidateCoord.X][candidateCoord.Y].get();
                                if (candidate != nullptr)
                                {
                                    element->SetNeighbour(candidate, dir);
                                }
                            }
                        }
                    }
                }
            }
        });
    }

    void GenerateNavMesh(Map& map)
    {
        map.ForeachLevel([&](MapLayer& layer)
        {
            NavMesh navMesh(MapConstants::MapSize_x, MapConstants::MapSize_y);

            MapElementCollection<MapElement_Floor>& collection = layer.GetElementList<MapElement_Floor>();
            uPoint size = collection.Size();

            for (unsigned int x = 0; x < size.X; ++x)
            {
                for (unsigned int y = 0; y < size.Y; ++y)
                {
                    MapElement_Floor* element = collection[x][y].get();
                    if (element != nullptr)
                    {
                        navMesh[x][y] = std::make_unique <AStarNode<MapElement_Floor>>(*element);
                    }
                }
            }

            for (unsigned int x = 0; x < size.X; ++x)
            {
                for (unsigned int y = 0; y < size.Y; ++y)
                {
                    AStarNode<MapElement_Floor>* element = navMesh[x][y].get();
                    if (element != nullptr)
                    {
                        for (int i = 0; i < Cardinal::DirectionCount_Basic; ++i)
                        {
                            Cardinal::Direction dir = Cardinal::ToDirection(i);
                            Point candidateCoord = Cardinal::GetCardinalPoint(dir);
                            candidateCoord.X += x;
                            candidateCoord.Y += y;

                            if (static_cast<unsigned int>(candidateCoord.X) < size.X &&
                                static_cast<unsigned int>(candidateCoord.Y) < size.Y)
                            {
                                AStarNode<MapElement_Floor>* neighbour = navMesh[candidateCoord.X][candidateCoord.Y].get();

                                if (neighbour != nullptr)
                                {
                                    element->AddNeighbour(*neighbour);
                                }
                            }
                        }
                    }
                }
            }

            layer.SetNavMesh(std::move(navMesh));
        });
    }
}