#pragma once
#define EPSILON 0.001f
#define PI 3.14159f

namespace WickedSick
{
  template <typename T>
  T clamp(const T& n, const T& lower, const T& upper) 
  {
    return std::max(lower, std::min(n, upper));
  }
}

