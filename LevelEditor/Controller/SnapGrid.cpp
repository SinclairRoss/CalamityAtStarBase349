#include "SnapGrid.h"

#include <math.h>

SnapGrid::SnapGrid()
{}

Vector2 SnapGrid::SnapCoordinates(const Vector2& worldCoordinates)
{
    Vector2 snapCoordinates;

    float x = worldCoordinates.X;
    float y = worldCoordinates.Y;

    snapCoordinates.X = floor(x) + 0.5f;
    snapCoordinates.Y = floor(y) + 0.5f;

    return snapCoordinates;
}