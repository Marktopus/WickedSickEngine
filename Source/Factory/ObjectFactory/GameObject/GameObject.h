#pragma once

#include "Component.h"

namespace WickedSick
{
  class GameObject
  {
  public:
    GameObject(int goID);
    GameObject(const GameObject& rhs);

    void Clone(GameObject* newObj);
    int GetID();
    void AddComponent(Component* newComp);
    Component* GetComponent(Component::Type type);
    
  private:
    Component* components_[Component::Count];
    int go_id_;
  };
}
