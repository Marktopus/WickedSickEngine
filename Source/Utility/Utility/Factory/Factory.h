#pragma once

#include "Utility/UtilityInterface.h"
#include "Archetype.h"

namespace WickedSick
{
  template <typename T>
  class Factory
  {
  public:
    Factory()
    {

    }

    void LoadArchetypes(const std::string& dir)
    {
    }

    T& Make(const std::string& archetypeName)
    {
      auto& archetype = archetype_map_.find(archetypeName);
      archetype.type->
      return manager_.New()
    }

    T& Make(const Archetype<T>& archetype)
    {

    }

    void Destroy(T& toDestroy)
    {

    }
  private:
    HashMap<std::string, Archetype<T> > archetype_map_;
    MemoryManager<T> manager_;
  };
}
