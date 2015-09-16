#pragma once
#include "Math/MathInterface.h"

namespace WickedSick
{

  struct Vertex
  {
    bool operator==(const Vertex& rhs);
    Vector3 position;
    Vector4 color;
    Vector3 normal;

    std::string to_string();
    void Print();
    //Vector2 tex;
  };
}
