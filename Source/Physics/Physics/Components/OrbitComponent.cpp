#include "PhysicsPrecompiled.h"
#include "OrbitComponent.h"

namespace WickedSick
{
  PHYSICSDLL_API OrbitComponent::OrbitComponent(Vector3 initialVec,
                                                Vector3 target, 
                                                float targetDist,
                                                float force)
                                                : targeting_(true),
                                                  force_(force),
                                                  target_dist_(targetDist),
                                                  current_dir_(initialVec.GetNormalized()),
                                                  target_(target),
                                                  Component(CT_OrbitComponent)
  {
  }

  PHYSICSDLL_API OrbitComponent::~OrbitComponent()
  {
  }

  PHYSICSDLL_API void OrbitComponent::Initialize()
  {
  }

  PHYSICSDLL_API void OrbitComponent::Update(float dt)
  {
    if (targeting_)
    {
      PhysicsComponent* pComp = (PhysicsComponent*) GetSibling(CT_PhysicsComponent);
      if(pComp)
      {
        if(pComp->GetRigidBody()->GetState().Velocity.IsZero())
        {
          pComp->GetRigidBody()->AddForce(current_dir_ * force_);
        }
        else
        {
          Transform* tr = (Transform*) GetSibling(CT_Transform);
          
          Vector3 toTarget = target_ - tr->GetPosition();

          float bias = toTarget.LengthSq() / (target_dist_/ 5.0f);
          bias = std::max(5.0f, bias);

          pComp->GetRigidBody()->AddForce(toTarget.GetNormalized() * bias * dt);

        }
      }
    }
  }

  PHYSICSDLL_API std::string OrbitComponent::GetName()
  {
    return "OrbitComponent";
  }

  PHYSICSDLL_API void OrbitComponent::Release()
  {
    targeting_ = false;
  }

  PHYSICSDLL_API void OrbitComponent::Target()
  {
    targeting_ = true;
  }

  PHYSICSDLL_API void OrbitComponent::SetCurrentDir(const Vector3& dir)
  {
    current_dir_ = dir.GetNormalized();
  }

  PHYSICSDLL_API void OrbitComponent::SetTarget(const Vector3& target)
  {
    target_ = target;
  }

  PHYSICSDLL_API void OrbitComponent::SetForce(float force)
  {
    force_ = force;
  }

  PHYSICSDLL_API void OrbitComponent::SetTargetDist(float dist)
  {
    target_dist_ = dist;
  }
}

