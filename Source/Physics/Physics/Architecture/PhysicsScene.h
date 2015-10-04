#pragma once

#include "Physics/PhysicsDLL.h"
#include "Resolution/Contact.h"

namespace WickedSick
{
  class Collider;
  class Physics;
  class RigidBody;
  class BroadPhase;
  class PhysicsComponent;
  class Octree;
  class PhysicsScene
  {
    public:
      PHYSICSDLL_API PhysicsScene();
      PHYSICSDLL_API ~PhysicsScene();

      PHYSICSDLL_API void Initialize();

      PHYSICSDLL_API void Update(float dt);

      PHYSICSDLL_API void Integrate(float dt);
      PHYSICSDLL_API void CheckCollisions();
      PHYSICSDLL_API void ResolveCollisions(float dt);
    
      PHYSICSDLL_API void UnloadScene();
      PHYSICSDLL_API void LoadScene();

      PHYSICSDLL_API void SetLoaded(bool loaded);
      PHYSICSDLL_API void AddPhysicsObject(PhysicsComponent* comp);

      PHYSICSDLL_API void Refresh();

      PHYSICSDLL_API void AddCollider(Collider* coll);
      
      PHYSICSDLL_API std::vector<RigidBody*>& GetRigidBodies();

      PHYSICSDLL_API BroadPhase* GetDynamicBroadphase();
      PHYSICSDLL_API BroadPhase* GetStaticBroadphase();
      PHYSICSDLL_API static bool GetIteration();
      
    private:
      std::vector<RigidBody*> rigid_bodies_;
      std::vector<Collider*> colliders_;

      BroadPhase* dynamic_broadphase_;
      BroadPhase* static_broadphase_;

      static bool resolution_iteration_;
      bool scene_loaded_;
      void find_basis(Contact& contact);
  };
}
