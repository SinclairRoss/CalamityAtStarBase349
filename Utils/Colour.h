#pragma once

#include <array>

struct Colour
{
    Colour();
    Colour(float r, float g, float b, float a);
    Colour(const Colour&) = default;

    void Set(const Colour& colour);
    void SetAlpha(float a);

    float R;
    float G;
    float B;
    float A;
};
