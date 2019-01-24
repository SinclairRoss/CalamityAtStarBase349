#include "MathsHelper.h"

const float MathsHelper::PI = 3.14159265359f;
const float MathsHelper::PI2 = 3.14159265359f * 2;
const float MathsHelper::PIOver2 = 3.14159265359f / 2;

float MathsHelper::Lerp(float val, float min, float max)
{
    return (min * (1.0f - val)) + (max * val);
}

float MathsHelper::Normalise(int val, int min, int max)
{
    return Normalise(static_cast<float>(val), static_cast<float>(min), static_cast<float>(max));
}

float MathsHelper::Normalise(float val, float min, float max)
{
    return Clamp((val - min) / (max - min), 0.0f, 1.0f);
}

float MathsHelper::SignedNormalise(float val, float min, float max)
{
    return Clamp((Normalise(val, min, max) - 0.5f) * 2, -1.0f, 1.0f);
}

float MathsHelper::Clamp(float val, float min, float max)
{
    if (val > max)
        val = max;
    else if (val < min)
        val = min;

    return val;
}

int MathsHelper::Clamp(int val, int min, int max)
{
    if (val > max)
        val = max;
    else if (val < min)
        val = min;

    return val;
}

float MathsHelper::Wrap(float val, float min, float max)
{
    float range = max - min + 1.0f;

    if (val < min)
    {
        val += range * ((min - val) / range + 1.0f);
    }

    float output = min + fmod(val - min, range);
    return output;
}

int MathsHelper::Wrap(int val, int min, int max)
{
    int range = max - min + 1;

    if (val < min)
    {
        val += range * ((min - val) / range + 1);
    }

    int output = min + (val - min) % range;
    return output;
}

int MathsHelper::NextP2(int a)
{
    int rval = 1;
    while (rval < a) rval <<= 1;
    return rval;
}