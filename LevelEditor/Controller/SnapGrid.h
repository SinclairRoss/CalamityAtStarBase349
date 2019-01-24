#pragma once

#include "Core\Math\Vector.h"

class SnapGrid
{
    public:
        SnapGrid();
        Vector2 SnapCoordinates(const Vector2& worldCoordinates);
};
