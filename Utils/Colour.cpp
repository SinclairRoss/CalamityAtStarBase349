#include "Colour.h"

Colour::Colour() :
    R(1.0f),
    G(1.0f),
    B(1.0f),
    A(1.0f)
{}

Colour::Colour(float r, float g, float b, float a) :
    R(r),
    G(g),
    B(b),
    A(a)
{}

void Colour::Set(const Colour& colour)
{
    R = colour.R;
    G = colour.G;
    B = colour.B;
    A = colour.A;
}