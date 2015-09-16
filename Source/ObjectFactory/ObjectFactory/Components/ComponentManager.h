#pragma once
#include "Utility/HashMap.h"
#include <string>

namespace WickedSick
{
  class Component;
  class ComponentFactoryBase;
  class GameObject;
  class ComponentManager
  {
  public:
    ComponentManager();
    ~ComponentManager();
    void Initialize();

    Component* CreateComponent( const std::string& name, 
                                const std::string& archetype,
                                GameObject* owner);

    ComponentFactoryBase* GetFactory(const std::string& name);

  private:

    HashMap<std::string, ComponentFactoryBase*> factory_map_;

  };
}
