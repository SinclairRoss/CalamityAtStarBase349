#pragma once

#include <array>
#include <assert.h>

#include "Core\Math\Vector.h"

namespace Cardinal
{
    enum class Direction : size_t
    {
        NORTH,
        SOUTH,
        EAST,
        WEST,
        NORTH_EAST,
        NORTH_WEST,
        SOUTH_EAST,
        SOUTH_WEST,

        _COUNT,
        _INVALID
    };

    constexpr int DirectionCount = 8;
    constexpr int DirectionCount_Basic = 4;

    extern const std::array<Vector2, 8> Vector;
    extern const std::array<Point, 8> iVector;


    extern Vector2 GetCardinalVector(Direction dir);
    extern Point GetCardinalPoint(Direction dir);

    extern int ToInt(Direction dir);
    extern Direction ToDirection(int dir);
}