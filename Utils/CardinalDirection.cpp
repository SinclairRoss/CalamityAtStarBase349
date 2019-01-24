#include "CardinalDirection.h"

namespace Cardinal
{
    const std::array<Vector2, 8> Vector =
    {
        {
            { 0.0f,  1.0f },   // North
            { 0.0f, -1.0f },   // South
            { 1.0f,  0.0f },   // East
            { -1.0f,  0.0f },  // West
            { 0.707106f,  0.707106f },   // North East
            { -0.707106f,  0.707106f },   // North West
            { 0.707106f, -0.707106f },   // South East
            { -0.707106f, -0.707106f },   // South West
            
        }
    };

    const std::array<Point, 8> iVector =
    {
        {
            {  0,  1 }, // North
            {  0, -1 }, // South
            {  1,  0 }, // East
            { -1,  0 }, // West
            { 1,  1 }, // North East
            { -1,  1 }, // North West
            { 1, -1 }, // South East
            { -1, -1 }, // South West
        }
    };

    Vector2 GetCardinalVector(Direction dir)
    {
        assert(dir != Direction::_COUNT && dir != Direction::_INVALID);

        size_t index = static_cast<size_t>(dir);
        return Vector[index];
    }

    Point GetCardinalPoint(Direction dir)
    {
        assert(dir != Direction::_COUNT && dir != Direction::_INVALID);

        size_t index = static_cast<size_t>(dir);
        return iVector[index];
    }

    int ToInt(Direction dir)
    {
        assert(dir != Direction::_COUNT && dir != Direction::_INVALID);
        return static_cast<int>(dir);
    }

    Direction ToDirection(int dir)
    {
        assert(dir >= 0 && dir < DirectionCount);
        return static_cast<Direction>(dir);
    }
}