#pragma once

#include "Core/CoreInterface.h"
#include "GraphicsDLL.h"

namespace WickedSick
{

  class CameraComponent : public Component
  {
  public:
    GRAPHICSDLL_API CameraComponent();
    GRAPHICSDLL_API ~CameraComponent();
    GRAPHICSDLL_API void Initialize();
    GRAPHICSDLL_API void Update(float dt);
    GRAPHICSDLL_API std::string GetName();
    GRAPHICSDLL_API void SetLookAt(const Vector3& lookat);
    GRAPHICSDLL_API Vector3 GetLookAt();
  private:
    Vector3 look_at_;
  };
}
