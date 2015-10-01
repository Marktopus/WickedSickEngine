#pragma once
#include "Core/CoreInterface.h"
#include "PhysicsComponent.h"

#include "PhysicsDLL.h"

namespace WickedSick
{
  class OrbitComponent : public Component
  {
  public:
    PHYSICSDLL_API OrbitComponent(Vector3 initialVec = Vector3(1.0f, 1.0f, 1.0f), 
                                  Vector3 target = Vector3(),
                                  float targetDist = 20.0f,
                                  float force = 10.0f);
    PHYSICSDLL_API ~OrbitComponent();

    PHYSICSDLL_API void Initialize() override;
    PHYSICSDLL_API void Update(float dt) override;
    PHYSICSDLL_API std::string GetName() override;

    PHYSICSDLL_API void Release();
    PHYSICSDLL_API void Target();
  private:
    bool targeting_;
    float force_;
    float target_dist_;
    Vector3 current_dir_;
    Vector3 target_;

  };
}
