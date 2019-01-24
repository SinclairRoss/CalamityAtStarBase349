#pragma once

#include <functional>
#include <array>

#include "Core\Physics\Collisions\CollisionDetection\collisiondetection.h"

#include "Map\MapElements\MapElement.h"
#include "GameConstants\TileData\ElementData.h"

#include "Core\Math\Vector.h"
#include "Core\Utils\Utils.h"
#include "Core\Utils\Vector2D.h"

#include "GameConstants\TileData\Utils\BrushTypes.h"

template <typename T>
class MapElementCollection
{
    public:
        MapElementCollection(float collectionZDepth, size_t mapSizeX, size_t mapSizeY) :
            m_Size(mapSizeX, mapSizeY),
            m_ElementList(mapSizeX, mapSizeY),
            m_CollectionZDepth(collectionZDepth)
        {}

        MapElementCollection(MapElementCollection&& other) noexcept :
            m_Size(other.m_Size),
            m_ElementList(std::move(other.m_ElementList)),
            m_CollectionZDepth(m_CollectionZDepth)
        {}

        void AddElement(const typename BrushType<T>::ElementData& data, typename BrushType<T>::ElementInstanceData& instanceData, const Vector2& position, int rotationIndex)
        {
            uPoint gridCoords = Utils::WorldToGridCoords(position);
            if (gridCoords.X < m_Size.X && gridCoords.Y < m_Size.Y)
            {
                Vector2 worldCoords = Utils::GridToWorldCoords(gridCoords);

                std::unique_ptr<T> tile = std::make_unique<T>(data, instanceData, worldCoords, rotationIndex);
                m_ElementList[gridCoords.X][gridCoords.Y] = std::move(tile);
            }
        }

        void ClearElement(const Vector2& position)
        {
            uPoint gridCoords = Utils::WorldToGridCoords(position);

            if (gridCoords.X < m_Size.X && gridCoords.Y < m_Size.Y)
            {
                m_ElementList[gridCoords.X][gridCoords.Y] = nullptr;
            }
        }

        T* GetElement(const Vector2& position) { return const_cast<T*>(static_cast<const MapElementCollection&>(*this).GetElement(position)); }
        const T* GetElement(const Vector2& position) const
        {
            T* element = nullptr;

            uPoint gridCoords = Utils::WorldToGridCoords(position);
            if (gridCoords.X < m_Size.X && gridCoords.Y < m_Size.Y)
            {
                element = m_ElementList[gridCoords.X][gridCoords.Y].get();
            }

            return element;
        }

        void ForeachElement(std::function<void(const T*)> func) const
        {
            for (unsigned int x = 0; x < m_Size.X; ++x)
            {
                for (unsigned int y = 0; y < m_Size.Y; ++y)
                {
                    func(m_ElementList[x][y].get());
                }
            }
        }

        void ForeachElement(std::function<void(T*)> func)
        {
            for (unsigned int x = 0; x < m_Size.X; ++x)
            {
                for (unsigned int y = 0; y < m_Size.Y; ++y)
                {
                    func(m_ElementList[x][y].get());
                }
            }
        }

        void Clear() 
        {
            for (unsigned int x = 0; x < m_Size.X; ++x)
            {
                for (unsigned int y = 0; y < m_Size.Y; ++y)
                {
                    m_ElementList[x][y].reset();
                    m_ElementList[x][y] = nullptr;
                }
            }
        }

        std::vector<std::unique_ptr<T>>& operator[](size_t index) { return m_ElementList[index]; }

        uPoint Size() const { return m_Size; }

    private:

        const uPoint m_Size;

        Vector2D<std::unique_ptr<T>> m_ElementList;
        float m_CollectionZDepth;
};