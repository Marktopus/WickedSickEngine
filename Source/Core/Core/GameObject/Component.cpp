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
                                      active_(false)
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

  COREDLL_API bool Component::GetActive()
  {
    return active_;
  }

  COREDLL_API void Component::Activate()
  {
    active_ = true;
  }

  COREDLL_API void Component::Deactivate()
  {
    active_ = false;
  }

  COREDLL_API void Component::SetDebug(bool newDebug)
  {
    render_debug_ = newDebug;
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

  COREDLL_API void Component::render_debug()
  {

  }

}
