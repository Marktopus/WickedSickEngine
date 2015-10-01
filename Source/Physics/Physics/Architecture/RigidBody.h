#pragma once

#include "PhysicsDLL.h"
#include "Resolution/Constraint.h"
#include "Resolution/ConstraintList.h"
#include "MotionState.h"

namespace WickedSick
{
  class Collider;
  class PhysicsComponent;
  class RigidBody
  {
    public:
      PHYSICSDLL_API RigidBody( PhysicsComponent* base,
                                bool isStatic = false,
                                float mass = 0.0f,
                                float inertiaTensor = 0.0f,
                                Vector3 position = Vector3(),
                                Vector3 centerofmass = Vector3(),
                                float gravityScalar = 1.0f,
                                float linearDamping = 0.01f,
                                float angularDamping = 0.01f);

      PHYSICSDLL_API void Integrate(const float& dt);
      PHYSICSDLL_API void AddForce(Vector3 force);
      PHYSICSDLL_API void AddTorque(Vector3 torque);
      




      PHYSICSDLL_API void clone(const RigidBody& rhs);

      PHYSICSDLL_API void SetPosition(Vector3 pos);
      PHYSICSDLL_API void SetGravityScalar(float scalar);
      PHYSICSDLL_API void SetVelocity(Vector3 vel);
      PHYSICSDLL_API void SetAngularVelocity(Vector3 vel);
      PHYSICSDLL_API void SetBase(PhysicsComponent* base);
      PHYSICSDLL_API void SetStatic(bool isStatic);



      PHYSICSDLL_API bool IsStatic();
      PHYSICSDLL_API float GetGravityScalar();
      PHYSICSDLL_API MotionState& GetState();
      PHYSICSDLL_API MotionState& GetPreviousState();
      PHYSICSDLL_API std::vector<Collider*>& GetColliders();
      PHYSICSDLL_API ConstraintList& GetConstraints();
      //std::vector<Collider*> GetCollisionsWith(const std::string& collider);
      PHYSICSDLL_API PhysicsComponent* GetBase();

    private:
      void stop_movement();
      void reset_orientation();
      void render_debug();

      float                     gravity_scalar_;
      float                     linear_damping_;
      float                     angular_damping_;
      MotionState               state_;
      MotionState               previous_state_;
      std::vector<Collider*>    colliders_; 
      ConstraintList            constraints_;
      bool                      static_;
      PhysicsComponent*         base_;

      bool draw_debug_;

  };
}                                                                
                