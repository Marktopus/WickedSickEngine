#pragma once

#include "Math/MathInterface.h"

namespace WickedSick
{
  struct Light
  {
  public:
  private:
    Vector3 dir_;
    float intensity_;
    Vector4 ambient_color_;
    Vector4 diffuse_color_;
  };
}