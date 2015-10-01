#pragma once
#include "Architecture/RigidBody.h"
#include "PhysicsDLL.h"
#include "Core/CoreInterface.h"
namespace WickedSick
{
  class RigidBody;
  class Collider;
  class PhysicsMesh;
  struct PhysicsMaterial;
  class PhysicsComponent : public Component
  {
    public:
      
      PHYSICSDLL_API PhysicsComponent(bool isStatic = false,
                                      float mass = 1.0f,
                                      float inertiaTensor = 0.0f,
                                      Vector3 position = Vector3(),
                                      Vector3 centerofmass = Vector3(),
                                      float gravityScalar = 1.0f,
                                      float linearDamping = 0.01f,
                                      float angularDamping = 0.01f);
      PHYSICSDLL_API ~PhysicsComponent();
      PHYSICSDLL_API void clone(const PhysicsComponent& rhs);
      PHYSICSDLL_API void SetPosition(Vector3 pos);

      PHYSICSDLL_API Vector3 GetPosition();
      PHYSICSDLL_API Vector3 GetVelocity();
      PHYSICSDLL_API void Initialize() override;
      PHYSICSDLL_API void Update(float dt) override;
      PHYSICSDLL_API std::string GetName() override;

      PHYSICSDLL_API std::set<PhysicsComponent*> GetCollisions();

      PHYSICSDLL_API void AddCollider(Collider* collider);
      PHYSICSDLL_API void AddCollider(RigidBody* base,
                                      PhysicsMaterial* material,
                                      PhysicsMesh* mesh,
                                      Matrix3 orientation_matrix = Matrix3(),
                                      float volume = 1.0f);
      PHYSICSDLL_API RigidBody* GetRigidBody();

    private:
      RigidBody body_; //box in here
      
      
  };
}

