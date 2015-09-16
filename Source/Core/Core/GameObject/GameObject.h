#pragma once

#include "Component.h"
#include "Transform.h"
#include "Utility/UtilityInterface.h"

namespace WickedSick
{
  class GameObject
  {
  public:
    COREDLL_API GameObject(int goID = invalidID);
    COREDLL_API GameObject(GameObject && rhs);
    COREDLL_API GameObject(const GameObject& rhs);

    COREDLL_API void Initialize();
    COREDLL_API void Clone(GameObject* newObj);
    COREDLL_API int GetID() const;
    COREDLL_API void SetID(int id);
    COREDLL_API void Activate();
    COREDLL_API void Deactivate();
    COREDLL_API bool GetActive();
    COREDLL_API void AddComponent(Component* newComp);
    COREDLL_API bool Valid() const;
    COREDLL_API Component* GetComponent(ComponentType type);
    static const int invalidID = -1;
  private:
    static Factory<Transform> transforms_;
	//asdfsf<asdfds/>
    std::string archetype_name_;
    std::string name_;
    Component* components_[CT_Count];
    int go_id_;
    bool active_;
  };
}
