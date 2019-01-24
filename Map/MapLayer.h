#pragma once

#include <functional>
#include <vector>

#include "Utils\MapElementCollection.h"

#include "GameConstants\TileData\Floor\ElementData_Floor.h"
#include "MapElements\Floor\MapElement_Floor.h"

#include "GameConstants\TileData\Wall\ElementData_Wall.h"
#include "MapElements\Wall\MapElement_Wall.h"

#include "MapElements\Bounds\MapBound.h"

#include "GameConstants\TileData\Interactables\ElementData_Interactable.h"
#include "GameObjects\Interactables\Interactable.h"

#include "GameConstants\TileData\Utils\BrushTypes.h"
#include "Utils\Types.h"

class MapLayer
{
    public:
        MapLayer(int zDepth);
        ~MapLayer() = default;

        MapLayer(const MapLayer&) = delete;
        MapLayer& operator=(const MapLayer&) = delete;

        MapLayer(MapLayer&&) noexcept = default;
        MapLayer& operator=(MapLayer&&) noexcept = default;

        template <typename T_MapElement>
        void AddElement(const typename BrushType<T_MapElement>::ElementData& data, typename BrushType<T_MapElement>::ElementInstanceData& elementData, const Vector2& position, int rotationIndex) { GetElementList<T_MapElement>().AddElement(data, elementData, position, rotationIndex); }

        template<typename T_MapElement>
        void ClearElement(const Vector2& position) { GetElementList<T_MapElement>().ClearElement(position); }

        template<typename T_MapElement>
        void ForeachElement(std::function<void(T_MapElement*)> func) { GetElementList<T_MapElement>().ForeachElement(func); }

        template<typename T_MapElement>
        void ForeachElement(std::function<void(const T_MapElement*)> func) const { GetElementList<T_MapElement>().ForeachElement(func); }

        template<typename T_MapElement>
        int GetNumElements() const { GetElementList<T_MapElement>().size(); }

        template<typename T_MapElement>
        const T_MapElement* GetElementAt(const Vector2& position) const { return GetElementList<T_MapElement>().GetElement(position); }

        template<typename T_MapElement>
        T_MapElement* GetElementAt(const Vector2& position) { return GetElementList<T_MapElement>().GetElement(position); }

        template <typename T_MapElement>
        MapElementCollection<T_MapElement>& GetElementList()
        {  static_assert(false, "No overload available for given types."); }

        template <typename T_MapElement>
        const MapElementCollection<T_MapElement>& GetElementList() const
        {  static_assert(false, "No overload available for given types."); }

        template <>
        MapElementCollection<MapElement_Floor>& GetElementList<MapElement_Floor>() 
        { return m_Elements_Floor; }

        template <>
        const MapElementCollection<MapElement_Floor>& GetElementList<MapElement_Floor>() const
        { return m_Elements_Floor; }

        template <>
        MapElementCollection<MapElement_Wall> & GetElementList<MapElement_Wall>()
        { return m_Elements_Wall; }

        template <>
        const MapElementCollection<MapElement_Wall> & GetElementList<MapElement_Wall>() const
        { return m_Elements_Wall; }

        template <>
        MapElementCollection<Interactable> & GetElementList<Interactable>()
        { return m_Elements_Interactable; }

        template <>
        const MapElementCollection<Interactable> & GetElementList<Interactable>() const
        { return m_Elements_Interactable; }

        AStarNode<MapElement_Floor>* GetPathingNode(const Vector2& position);

        void SetNavMesh(NavMesh&& navMesh);
        void AddBounds(Vector2& position, Vector2& size);

    private:

        MapElementCollection<MapElement_Floor> m_Elements_Floor;
        MapElementCollection<MapElement_Wall> m_Elements_Wall;
        MapElementCollection<Interactable> m_Elements_Interactable;

        NavMesh m_NavMesh;
		std::vector<MapBound> m_BoundsData;
};
