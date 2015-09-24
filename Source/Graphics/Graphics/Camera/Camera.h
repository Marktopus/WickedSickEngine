#pragma once

#include "Math/MathInterface.h"
#include "Graphics/GraphicsDLL.h"

namespace WickedSick
{
  class CameraComponent;
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
    GRAPHICSDLL_API Vector3 GetLookAt();

    GRAPHICSDLL_API void Orient(float dt);
    
    GRAPHICSDLL_API void SetSource(CameraComponent* source);

    GRAPHICSDLL_API Matrix4 GetViewMatrix();

  private:
    CameraComponent* source_;
    Vector3 rot_;
    Vector3 pos_;
    Vector3 look_at_;

    Matrix4 view_;

  };
}