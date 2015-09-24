#include "CorePrecompiled.h"
#include "GameObject.h"

namespace WickedSick
{

  Factory<Transform> GameObject::transforms_;
  COREDLL_API GameObject::GameObject( int goID)
                                      : go_id_(goID),
                                        active_(false)
  {
    
    for (int i = 0; i < CT_Count; ++i)
    {
      components_[i] = nullptr;
    }
    AddComponent(transforms_.Create(this));
  }

  COREDLL_API GameObject::GameObject( GameObject&& rhs) 
                                      : go_id_(std::move(rhs.go_id_)),
                                        name_(std::move(rhs.name_)),
                                        active_(std::move(rhs.active_)),
                                        archetype_name_(std::move(rhs.archetype_name_))
  {
    for (int i = 0; i < CT_Count; ++i)
    {
      components_[i] = rhs.components_[i];
      if (components_[i])
      {
        components_[i]->SetOwner(this);
      }
      rhs.components_[i] = nullptr;
    }
  }

  COREDLL_API GameObject::GameObject( const GameObject& rhs) 
                                      : name_(rhs.name_),
                                        archetype_name_(rhs.archetype_name_)
  {
    for (int i = 0; i < CT_Count; ++i)
    {
      components_[i] = nullptr;
    }
  }


  COREDLL_API bool GameObject::Valid() const
  {
    return go_id_ != GameObject::invalidID;
  }

  COREDLL_API Component * GameObject::GetComponent(ComponentType type)
  {
    return components_[type];
  }

  COREDLL_API int GameObject::GetID() const
  {
    return go_id_;
  }

  COREDLL_API std::string GameObject::GetArchetypeName() const
  {
    return archetype_name_;
  }

  COREDLL_API std::string GameObject::GetName() const
  {
    return name_;
  }

  COREDLL_API void GameObject::SetID(int id)
  {
    go_id_ = id;
  }

  COREDLL_API void GameObject::SetArchetypeName(const std::string& name)
  {
    archetype_name_ = name;
  }

  COREDLL_API void GameObject::SetName(const std::string& name)
  {
    name_ = name;
  }

  COREDLL_API void GameObject::Activate()
  {
    active_ = true;
    for(auto& it : components_)
    {
      if(it)
      {
        it->Activate();
      }
    }
  }

  COREDLL_API void GameObject::Deactivate()
  {
    active_ = false;
    for (auto& it : components_)
    {
      if(it)
      {
        it->Deactivate();
      }
    }
  }


  COREDLL_API bool GameObject::GetActive()
  {
    return active_;
  }

  COREDLL_API void GameObject::Initialize()
  {
    for (auto& it : components_)
    {
      if (it)
      {
        it->Initialize();
      }
    }
  }

  COREDLL_API void GameObject::Clone(GameObject* newObj)
  {

  }

  COREDLL_API void GameObject::AddComponent(Component* newComp)
  {
    if(newComp)
    {
      components_[newComp->GetType()] = newComp;
      newComp->SetOwner(this);
    }
  }

}
