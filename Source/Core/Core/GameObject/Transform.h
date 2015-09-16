#pragma once
#include "Math/MathInterface.h"
#include "Component.h"

#include "CoreDLL.h"

namespace WickedSick
{
  class GameObject;
#define MINSCALE 0.01f
  class Transform : public Component
  {
  public:
    
    COREDLL_API Transform(GameObject*     owner = nullptr,
							            const Vector3&  pos    = Vector3(),
							            const Vector3&  scale  = Vector3(1.0f, 1.0f, 1.0f),
							            const Vector3&  rot    = Vector3());
    
    COREDLL_API Transform(const Transform& rhs);

    COREDLL_API ~Transform();

    COREDLL_API void Initialize();

    COREDLL_API std::string GetName();

    COREDLL_API Vector3 GetPosition();
    COREDLL_API void SetPosition(const Vector3& pos);
    COREDLL_API void SetPosition( float x, 
                                  float y, 
                                  float z);

    COREDLL_API Vector3 GetRotation();
    COREDLL_API void SetRotation(const Vector3& rot);
    COREDLL_API void SetRotation( float x, 
                                  float y, 
                                  float z);

    COREDLL_API Vector3 GetScale();
    COREDLL_API void SetScale(const Vector3& scale);
    COREDLL_API void SetScale(float x, 
                              float y, 
                              float z);
    COREDLL_API void SetScale(float scale);


  private:
    const std::string name_;
    Vector3 pos_;
    Vector3 scale_;
    Vector3 rot_;
  };
}