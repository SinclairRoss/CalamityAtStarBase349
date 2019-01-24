#pragma once

#include <functional>
#include <vector>

#include "Core\Math\Vector.h"

namespace Utils
{
    template<typename T>
    size_t IndexOf(std::vector<T>& vec, const T& obj)
    {
        std::vector<T>::const_iterator iter = std::find(vec.begin(), vec.end(), obj);
        size_t index = (iter != vec.end()) ? std::distance(vec.cbegin(), iter) : -1;

        return index;
    }

    template<typename T>
    size_t IndexOf_If(const std::vector<T>& vec, std::function<bool(const T&)> predicate)
    {
        std::vector<T>::const_iterator iter = std::find_if(vec.begin(), vec.end(), predicate);
        size_t index = (iter != vec.end()) ? std::distance(vec.cbegin(), iter) : -1;

        return std::distance(vec.begin(), iter);
    }

    extern uPoint WorldToGridCoords(const Vector2& worldCoordinates);
    extern Vector2 GridToWorldCoords(const uPoint& gridCoordinates);
}
