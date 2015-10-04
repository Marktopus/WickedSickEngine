
#include "PhysicsPrecompiled.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Components\PhysicsComponent.h"

#include "PhysicsScene.h"
//#include "Octree.h"

#include "System/Physics.h"

//debug draw
#include "PhysicsMesh.h"
//


namespace WickedSick
{

  PHYSICSDLL_API RigidBody::RigidBody( PhysicsComponent * base,
                                       bool isStatic,
                                       float mass,
                                       float inertiaTensor,
                                       Vector3 position,
                                       Vector3 centerofmass,
                                       float gravityScalar,
                                       float linearDamping,
                                       float angularDamping)
                                        : state_( mass,
                                                  inertiaTensor,
                                                  position,
                                                  centerofmass),
                                          static_(isStatic),
                                          gravity_scalar_(gravityScalar),
                                          angular_damping_(angularDamping),
                                          linear_damping_(linearDamping),
                                          base_(base),
                                          draw_debug_(false)
  {
    previous_state_ = state_;
  }

  PHYSICSDLL_API bool RigidBody::IsStatic() 
  { 
    return static_; 
  }

  PHYSICSDLL_API void RigidBody::clone(const RigidBody& rhs)
  {
    draw_debug_ = rhs.draw_debug_;
    gravity_scalar_ = rhs.gravity_scalar_;
    linear_damping_ = rhs.linear_damping_;
    angular_damping_ = rhs.angular_damping_;
    state_ = rhs.state_;
    previous_state_ = rhs.previous_state_;
    static_ = rhs.static_;
    for(auto it : rhs.colliders_)
    {
      colliders_.push_back(new Collider(this));
      colliders_.back()->clone(*it);
    }
  }

  PHYSICSDLL_API void RigidBody::SetPosition(Vector3 pos) 
  { 
    stop_movement();
    reset_orientation();
    state_.SetPosition(pos); 
    if(static_)
    {
      previous_state_.SetPosition(pos);
    }
  }

  PHYSICSDLL_API void RigidBody::SetGravityScalar(float scalar)
  {
    gravity_scalar_ = scalar;
  }

  PHYSICSDLL_API float RigidBody::GetGravityScalar()
  {
    return gravity_scalar_;
  }

  PHYSICSDLL_API MotionState & RigidBody::GetState() 
  { 
    return state_; 
  }

  PHYSICSDLL_API MotionState& RigidBody::GetPreviousState() 
  { 
    return previous_state_; 
  }

  PHYSICSDLL_API std::vector<Collider*>& RigidBody::GetColliders() 
  { 
    return colliders_; 
  }

  PHYSICSDLL_API ConstraintList& RigidBody::GetConstraints() 
  { 
    return constraints_; 
  }

  //std::vector<Collider*> GetCollisionsWith(const std::string& collider);

  PHYSICSDLL_API PhysicsComponent * RigidBody::GetBase() 
  { 
    return base_; 
  }

  PHYSICSDLL_API void RigidBody::SetVelocity(Vector3 vel)
  {
    previous_state_.Velocity = vel;
    state_.Velocity = vel;
  }

  PHYSICSDLL_API void RigidBody::SetAngularVelocity(Vector3 vel)
  {
    previous_state_.AngularVelocity = vel;
    state_.AngularVelocity = vel;
  }

  PHYSICSDLL_API void RigidBody::SetBase(PhysicsComponent * base) 
  { 
    base_ = base; 
  }

  PHYSICSDLL_API void RigidBody::SetStatic(bool isStatic) 
  { 
    static_ = isStatic; 
  }

  PHYSICSDLL_API void RigidBody::AddForce(Vector3 force)
  {
    state_.Force += force;
  }

  void RigidBody::stop_movement()
  {
    state_.StopMovement();
  }

  void RigidBody::reset_orientation()
  {
    state_.ResetOrientation();
  }

  void RigidBody::render_debug()
  {

  }

  PHYSICSDLL_API void RigidBody::AddTorque(Vector3 torque)
  {
    state_.Torque += torque;
  }

  PHYSICSDLL_API void RigidBody::Integrate(const float& dt)
  {

    if(draw_debug_)
    {
      render_debug();
    }

    previous_state_ = state_;
    if(!static_)
    {
      state_.Position += state_.Velocity * dt;
      //state_.CenterOfMass += state_.Velocity * dt;
      state_.Orientation += state_.AngularVelocity * dt;

      //gravity here
      state_.Velocity += ((Physics::Gravity * gravity_scalar_) + (state_.Force * state_.InverseMass)) * dt;
      state_.AngularVelocity += (state_.Torque * state_.InverseInertiaTensor) * dt;

      //damping!
      state_.Velocity *= 1.0f / (1.0f + dt * linear_damping_);
      state_.AngularVelocity *= 1.0f / (1.0f + dt * angular_damping_);

      state_.Force = Vector3();
      state_.Torque = Vector3();
    }

    if(state_.Position != previous_state_.Position)
    {

      //todo: update broadphase
    }
  }

  }
