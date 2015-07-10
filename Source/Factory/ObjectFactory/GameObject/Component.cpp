#include "ObjectFactoryPrecompiled.h"
#include "Component.h"

namespace WickedSick
{
  Component::Component(Component::Type type, 
                       int compID)
                       :  type_(type),
                          comp_id_(compID)
  {

  }
  
  Component::~Component()
  {

  }

  Component::Type Component::GetType()
  {
    return type_;
  }

  int Component::GetID()
  {
    return comp_id_;
  }
}
