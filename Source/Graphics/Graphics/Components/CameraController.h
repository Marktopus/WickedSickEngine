#pragma once

#include "Core/CoreInterface.h"
#include "Math/MathInterface.h"
#include "GraphicsDLL.h"

namespace WickedSick
{

  class CameraController : public Component
  {
  public:
    GRAPHICSDLL_API CameraController();
    GRAPHICSDLL_API ~CameraController();
    GRAPHICSDLL_API void Initialize();
    GRAPHICSDLL_API void Update(float dt);
    GRAPHICSDLL_API std::string GetName();
  private:
    Vector2i last_mouse_pos_;
  };
}
