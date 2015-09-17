#pragma once

#include "MetaPrecompiled.h"
#include "Utility/SimplifyType.h"
#include "MetaSingleton.h"

namespace Reflection
{

  class Metadata;
  class MetaManager
  {
  public:
    static void RegisterMeta(Metadata* meta);

    static Metadata* Get(std::string name)
    {
      MetaMap& metas = getMetas();
      auto meta = metas.find(name);
      if (meta == metas.end())
      {
        return nullptr;
      }
      else
      {
        return meta->second;
      }
    }

    static void DefineConversions();

    typedef std::unordered_map<std::string, Metadata*> MetaMap;

    static MetaMap& getMetas()
    {
      static MetaMap metas;
      return metas;
    }
  };
}
