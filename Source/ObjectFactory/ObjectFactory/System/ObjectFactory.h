#pragma once

#include "Core/CoreInterface.h"
#include "Utility/UtilityInterface.h"
#include "Math/MathInterface.h"
#include "ObjectFactoryDLL.h"


namespace WickedSick
{

  class GameObject;
  class ComponentManager;
  class ObjectFactory : public System
  {
  public:
    OBJECTFACTORYDLL_API ObjectFactory();
    OBJECTFACTORYDLL_API ~ObjectFactory();
    OBJECTFACTORYDLL_API void Initialize();
    OBJECTFACTORYDLL_API bool Load();
    OBJECTFACTORYDLL_API bool Reload();
    OBJECTFACTORYDLL_API void Update(float dt);
    OBJECTFACTORYDLL_API void ReceiveMessage(Event * msg);
    OBJECTFACTORYDLL_API GameObject* CloneArchetype(const std::string& name);
    OBJECTFACTORYDLL_API GameObject* MakeBlank();

    OBJECTFACTORYDLL_API ComponentManager* GetComponentManager();
    
    //testing and hardcoded
    OBJECTFACTORYDLL_API void CreateArchetypes();
    OBJECTFACTORYDLL_API void BuildScene();
    ///////////////////////

  private:


    ComponentManager*   comp_manager_;
    Factory<GameObject> object_factory_;
    std::unordered_map<int, GameObject*> game_objects_;

    unsigned objects_created_;

    //static MemoryManager<GameObject> game_object_allocator_;


  };
}
