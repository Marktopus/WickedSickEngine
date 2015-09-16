#include "ObjectFactoryPrecompiled.h"
#include "ComponentManager.h"
#include "Core/CoreInterface.h"
#include "Components/ComponentFactory.h"
#include "Graphics/GraphicsInterface.h"
//#include ""

namespace WickedSick
{
  ComponentManager::ComponentManager()
  {
#define RegisterComponentType(x) factory_map_.insert(std::string(#x), (ComponentFactoryBase*)new ComponentFactory<x>());
#include "Core/GameObject/ComponentTypes.h"
#undef RegisterComponentType
  }

  ComponentManager::~ComponentManager()
  {
  }

  void ComponentManager::Initialize()
  {
    for (auto& it : factory_map_)
    {
      
    }
  }

  Component* ComponentManager::CreateComponent( const std::string & name, 
                                                const std::string& archetype, 
                                                GameObject* owner)
  {
    Component* newComp = nullptr;
    auto& factoryIt = factory_map_.find(name);
    if (factoryIt != factory_map_.end())
    {
      newComp = (*factoryIt).type->Make(archetype, owner);
    }
    return newComp;
  }

  ComponentFactoryBase* ComponentManager::GetFactory(const std::string& name)
  {
    auto& factoryIt = factory_map_.find(name);
    return (factoryIt != factory_map_.end()) ? (*factoryIt).type : nullptr;
  }

}
