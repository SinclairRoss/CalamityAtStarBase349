#include "Utils.h"

namespace Utils
{
    uPoint WorldToGridCoords(const Vector2& worldCoordinates)
    {
        unsigned int x = static_cast<unsigned int>(floor(worldCoordinates.X));
        unsigned int y = static_cast<int>(floor(worldCoordinates.Y));
        return uPoint(x, y);
    }

    Vector2 GridToWorldCoords(const uPoint& gridCoordinates)
    {
        float x = static_cast<float>(gridCoordinates.X) + 0.5f;
        float y = static_cast<float>(gridCoordinates.Y) + 0.5f;

        return Vector2(x, y);
    }
}
