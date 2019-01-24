#pragma once

#include "Core\Utils\Colour.h"
#include "Core\Renderables\Sprite.h"

class PointMarker : public Sprite
{
    public:
        PointMarker(float x, float y, const Colour& colour);

        void Update() override;
};
