#include "PhysicsPrecompiled.h"
#include "PhysicsComponent.h"
#include "Core/CoreInterface.h"

#include "Architecture/RigidBody.h"
#include "Architecture/PhysicsMesh.h"
#include "Architecture/Collider.h"

#include "Resolution/ContactEdge.h"

#include "System/Physics.h"

#include "Architecture/PhysicsScene.h"

namespace WickedSick
{
  PHYSICSDLL_API PhysicsComponent::PhysicsComponent(bool isStatic,
                                                    float mass,
                                                    float inertiaTensor,
                                                    Vector3 position,
                                                    Vector3 centerofmass,
                                                    float gravityScalar,
                                                    float linearDamping,
                                                    float angularDamping) 
                                                    : Component(CT_PhysicsComponent),
                                                      body_(this,
                                                            isStatic,
                                                            mass,
                                                            inertiaTensor,
                                                            position,
                                                            centerofmass,
                                                            gravityScalar,
                                                            linearDamping,
                                                            angularDamping)
  {
  }

  PHYSICSDLL_API void PhysicsComponent::clone(const PhysicsComponent& rhs)
  {
    body_.clone(rhs.body_);
  }

  PHYSICSDLL_API PhysicsComponent::~PhysicsComponent()
  {

  }


  PHYSICSDLL_API void PhysicsComponent::SetPosition(Vector3 pos)
  { 
    body_.SetPosition(pos); 
  }

  PHYSICSDLL_API std::set<PhysicsComponent*> PhysicsComponent::GetCollisions()
  {
    std::set<PhysicsComponent*> collidedWith;
    for(auto it : body_.GetColliders())
    {
      for(auto it : it->GetEdges())
      {
        collidedWith.insert(it->GetOther()->GetBase()->GetBase());
      }
    }
    return collidedWith;
  }

  PHYSICSDLL_API Vector3 PhysicsComponent::GetPosition()
  { 
    return body_.GetPreviousState().Position; 
  }
  
  PHYSICSDLL_API Vector3 PhysicsComponent::GetVelocity()
  { 
    return body_.GetPreviousState().Velocity; 
  }

  PHYSICSDLL_API void PhysicsComponent::Initialize()
  {
    Physics* pSys = (Physics*)Engine::GetCore()->GetSystem(ST_Physics);

    pSys->AddComponent(this);
    pSys->GetScene()->AddPhysicsObject(this);
  }

  PHYSICSDLL_API void PhysicsComponent::Update(float dt)
  {
  }

  PHYSICSDLL_API std::string PhysicsComponent::GetName()
  {
    return "PhysicsComponent";
  }

  PHYSICSDLL_API void PhysicsComponent::AddCollider(Collider* collider)
  { 
    body_.GetColliders().push_back(collider);
    //do this elsewhere...
    //GET_SYSTEM(Physics)->GetScene()->AddCollider(collider);
  }

  PHYSICSDLL_API void PhysicsComponent::AddCollider(RigidBody* base,
                                                    PhysicsMaterial* material,
                                                    PhysicsMesh* mesh,
                                                    Matrix3 orientation_matrix,
                                                    float volume)
  {
    body_.GetColliders().push_back(new Collider(base, 
                                                material, 
                                                mesh, 
                                                mesh->GetBoundingBox().max_, 
                                                0,
                                                orientation_matrix,
                                                true,
                                                volume));
    //again, elsewhere
    //GET_SYSTEM(Physics)->GetScene()->AddCollider(body_.GetColliders().back());
  }

  PHYSICSDLL_API RigidBody* PhysicsComponent::GetRigidBody()
  { 
    return &body_; 
  }
}
