#pragma once

#include <array>
#include <functional>

#include "Core\Utils\CardinalDirection.h"

template<typename T>
struct Neighbourhood
{
    std::array<T*, Cardinal::DirectionCount> m_Neighbours;

    void SetNeighbour(T* element, Cardinal::Direction dir) { m_Neighbours[Cardinal::ToInt(dir)] = element; }
    T* GetNeighbour(Cardinal::Direction dir) { return m_Neighbours[Cardinal::ToInt(dir)]; }
    const T* GetNeighbour(Cardinal::Direction dir) const { return m_Neighbours[Cardinal::ToInt(dir)]; }

    void ForeachNeighbour(std::function<bool(const T* neighbour, Cardinal::Direction dir)> func) const
    {
        for (int i = 0; i < Cardinal::DirectionCount; ++i)
        {
            T* neighbour = m_Neighbours[i];
            Cardinal::Direction dir = Cardinal::ToDirection(i);
            if (!func(neighbour, dir))
            {
                break;
            }
        }
    }
};