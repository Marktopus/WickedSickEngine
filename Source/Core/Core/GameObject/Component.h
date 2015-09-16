#pragma once

#include "CoreDLL.h"
#include <string>

namespace WickedSick
{
  class GameObject;
  enum ComponentType
  {
    #define RegisterComponentType(x) CT_##x,
    #include "ComponentTypes.h"
    #undef RegisterComponentType
    CT_Count
  };
  class Component
  {
  public:

    

    COREDLL_API Component(ComponentType        type = CT_Count, 
                          GameObject* owner = nullptr);
    COREDLL_API virtual ~Component();

    COREDLL_API virtual void Initialize() = 0;
    COREDLL_API virtual std::string GetName() = 0;

    COREDLL_API virtual ComponentType GetType() final;

    COREDLL_API virtual Component* GetSibling(ComponentType type) final;

    COREDLL_API virtual GameObject* GetOwner() final;
    COREDLL_API virtual void SetOwner(GameObject* newOwner) final;

  private:
    bool        active_;
    ComponentType        type_;
    GameObject* owner_;

  };
  
}
