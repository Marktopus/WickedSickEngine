#pragma once
#include "Math/MathInterface.h"

namespace WickedSick
{

  struct Vertex
  {
    bool operator==(const Vertex& rhs);
    Vector3 position;
    Vector3 normal;
    Vector4 color;

    std::string to_string();
    void Print();
    //Vector2 tex;
  };
}
