///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        1/21/2014
//Description: singleton class to handle all metadata
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#ifndef META_SINGLETON_H
#define META_SINGLETONH

#include "Metadata.h"


template <typename MetaType>
class MetaSingleton
{
  public:
    MetaSingleton()
    {
      RegisterTypeData();
    }
    static Metadata* Get()
    {
      return &metadata_;
    }

    template<typename baseType>
    class Derived
    {
      public:
        static Metadata* Get(){return metadata_;}
        static Metadata* metadata_;
    };

    static void RegisterTypeData(void);
    static Metadata metadata_;
  private:
};

template <typename MetaType>
class MetaSingleton<const MetaType> : public MetaSingleton<MetaType> {};

template <typename MetaType>
class MetaSingleton<MetaType&> : public MetaSingleton<MetaType> {};

template <typename MetaType>
class MetaSingleton<const MetaType&> : public MetaSingleton<MetaType> {};

template <typename MetaType>
class MetaSingleton<MetaType&&> : public MetaSingleton<MetaType> {};

template <typename MetaType>
class MetaSingleton<MetaType*> : public MetaSingleton<MetaType> {};

template <typename MetaType>
class MetaSingleton<const MetaType*> : public MetaSingleton<MetaType> {};



#endif
