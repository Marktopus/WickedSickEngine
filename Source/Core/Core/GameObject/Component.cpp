#include "CorePrecompiled.h"
#include "Component.h"
#include "Debugging/DebugInterface.h"
#include "GameObject.h"

namespace WickedSick
{
  COREDLL_API Component::Component( ComponentType type, 
                                    GameObject* owner)
                                    : type_(type),
                                      owner_(owner),
                                      active_(true)
  {
    if (!owner_)
    {
      ConsolePrint("Did you explicitly construct the base Component?");
    }
  }
  
  COREDLL_API Component::~Component()
  {

  }

  COREDLL_API ComponentType Component::GetType()
  {
    return type_;
  }

  COREDLL_API Component * Component::GetSibling(ComponentType type)
  {
    return owner_->GetComponent(type);
  }

  COREDLL_API GameObject * Component::GetOwner()
  {
    return owner_;
  }

  COREDLL_API void Component::SetOwner(GameObject* newOwner)
  {
    owner_ = newOwner;
  }
}
