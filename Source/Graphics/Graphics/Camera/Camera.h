#pragma once

#include "Math/MathInterface.h"
#include "Graphics/GraphicsDLL.h"

namespace WickedSick
{
  class Camera
  {
  public:
    GRAPHICSDLL_API Camera();
    GRAPHICSDLL_API ~Camera();

    GRAPHICSDLL_API void SetPosition(float x, float y, float z);
	  GRAPHICSDLL_API void SetPosition(const Vector3& pos);
    GRAPHICSDLL_API void SetRotation(float x, float y, float z);
	  GRAPHICSDLL_API void SetRotation(const Vector3& rot);

    GRAPHICSDLL_API Vector3 GetPosition();
    GRAPHICSDLL_API Vector3 GetRotation();

    GRAPHICSDLL_API void Orient();
    GRAPHICSDLL_API Matrix4 GetViewMatrix();

  private:
    Vector3 pos_;
    Vector3 rot_;
    const Vector4 up_;
    Vector4 look_at_;

    Matrix4 view_;

  };
}