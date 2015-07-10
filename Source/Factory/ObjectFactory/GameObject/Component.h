#pragma once

namespace WickedSick
{
  class Component
  {
  public:

    enum Type
    {
#define RegisterComponentType(x) x,
#include "ComponentTypes.h"
#undef RegisterComponentType
      Count
    };

    Component(Type type, int compID);
    virtual ~Component();

    virtual void Clone(Component* newComp) = 0;
    virtual Type GetType() final;
    virtual int GetID() final;

  private:
    Type type_;
    int comp_id_;

  };
  
}
