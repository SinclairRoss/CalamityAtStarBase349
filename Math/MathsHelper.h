#pragma once

#include <cmath>

#include "Matrix4.h"
#include "Vector.h"

namespace MathsHelper
{
   extern const float PI;
   extern const float PI2;
   extern const float PIOver2;

   float Lerp(float val, float min, float max);

   float Normalise(int val, int min, int max);
   float Normalise(float val, float min, float max);
   float SignedNormalise(float val, float min, float max);

   float Clamp(float val, float min, float max);
   int Clamp(int val, int min, int max);

   float Wrap(float val, float min, float max);
   int Wrap(int val, int min, int max);

   int NextP2(int a);
}