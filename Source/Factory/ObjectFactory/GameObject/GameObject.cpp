#include "ObjectFactoryPrecompiled.h"
#include "GameObject.h"

namespace WickedSick
{
  GameObject::GameObject(int goID)
                         : go_id_(goID)
  {

  }

  GameObject::GameObject(const GameObject& rhs)
  {

  }

  void GameObject::Clone(GameObject* newObj)
  {

  }

  void GameObject::AddComponent(Component* newComp)
  {
    components_[newComp->GetType()] = newComp;
  }

  


}
