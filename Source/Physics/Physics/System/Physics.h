#pragma once
#include "PhysicsDLL.h"
#include "Core/CoreInterface.h"

namespace WickedSick
{
  class PhysicsScene;
  struct PhysicsMaterial;
  class PhysicsMesh;
  class PhysicsComponent;
  class GameObject;
  class Event;
  class Physics : public System
  {
    public:
      PHYSICSDLL_API Physics();
      PHYSICSDLL_API ~Physics();

      PHYSICSDLL_API void Initialize() override;
      PHYSICSDLL_API bool Load() override;
      PHYSICSDLL_API bool Reload() override;
      PHYSICSDLL_API void Update(float dt) override;
      PHYSICSDLL_API void ReceiveMessage(Event* letter) override;

      PHYSICSDLL_API PhysicsMaterial* GetMaterial(const std::string& name);
      PHYSICSDLL_API PhysicsMesh* GetMesh(const std::string& name);
      PHYSICSDLL_API PhysicsScene * GetScene();
      

      PHYSICSDLL_API void AddComponent(PhysicsComponent* comp);
      PHYSICSDLL_API std::set<PhysicsComponent*>& GetComponents();

      static Vector3 Gravity;

    private:
      
      //everything is still valid after this remove function
      template <typename T>
      static void remove(std::vector<T>& vec, int index, int& last)
      {
        std::swap(vec[index], vec[last]);
        --last;
      }
      
      std::set<PhysicsComponent*> comps_;
      HashMap<std::string, PhysicsMaterial*>   materials_;
      HashMap<std::string, PhysicsMesh*>       meshes_;
      PhysicsScene*                   scene_;
  };
}
