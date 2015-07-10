#pragma once

#include "Core/CoreInterface.h"
#include "Utility/UtilityInterface.h"
#include "Math/MathInterface.h"
#include "ObjectFactoryDLL.h"
#include "GameObject/GameObject.h"

namespace WickedSick
{

  class GameObject;
  class ObjectFactory : public System
  {
  public:
    OBJECTFACTORYDLL_API ObjectFactory();
    OBJECTFACTORYDLL_API ~ObjectFactory();
    OBJECTFACTORYDLL_API void Initialize();
    OBJECTFACTORYDLL_API bool Load();
    OBJECTFACTORYDLL_API bool Reload();
    OBJECTFACTORYDLL_API void Update(double dt);
    OBJECTFACTORYDLL_API void ReceiveMessage(Message * msg);
    OBJECTFACTORYDLL_API GameObject* CloneArchetype(const std::string& name);
  private:

    Factory<GameObject> object_factory_;

    HashMap<int, GameObject*> game_objects_;
    //MemoryManager<GameObject> game_object_allocator_;


  };
}
