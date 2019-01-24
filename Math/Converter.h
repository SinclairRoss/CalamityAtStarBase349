#pragma once

#include "MathsHelper.h"

struct Converter
{
    float MinInput;
    float MaxInput;

    float MinOutput;
    float MaxOutput;

    float Convert(float inValue) const
    {
        float lerpVal = MathsHelper::Normalise(inValue, MinInput, MaxInput);
        return MathsHelper::Lerp(lerpVal, MinOutput, MaxOutput);
    }
};