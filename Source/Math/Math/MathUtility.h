#pragma once

#include "MathDLL.h"
#include "Vector/Vector3.h"
#include "Matrix/Matrix4.h"

#define EPSILON 0.001f
#define PI 3.14159f

namespace WickedSick
{
  template <typename T>
  T clamp(const T& n, const T& lower, const T& upper) 
  {
    return std::max(lower, std::min(n, upper));
  }

  MATHDLL_API float AngleBetween(const Vector3& left, const Vector3& right);

  MATHDLL_API Vector3 RotateAround(const Vector3 & axis, float amount, const Vector3 & vectorToRotate);

  MATHDLL_API Matrix4 CrossProductMatrix(const Vector3& n);
  MATHDLL_API Matrix4 TensorProductMatrix(const Vector3& n);
}

