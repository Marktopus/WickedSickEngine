#pragma once

#include "MetaDLL.h"

namespace Reflection
{

  class Metadata;


  class LuaUserdata;


  class Var
  {
    public:

      METADLL_API static void RegisterTypeData();
      METADLL_API Metadata* GetMetatype();

      METADLL_API Var(void);
      METADLL_API Var(Metadata* type, 
          void* data);
      METADLL_API Var(const Var& other);
      METADLL_API Var(LuaUserdata* data);
    
      METADLL_API ~Var();

      template<typename T>
      Var(T& data);
      template<typename T>
      Var(T&& data);
      template<typename T>
      Var(const T& data);
      template<>
      Var(LuaUserdata * const& tocopy);

      template<>
      Var(void * const& tocopy);




      template<typename T>
      T& GetValue(void);

      template<typename T>
      void SetValue(const T& value);
      template<typename T>
      void SetValue(T& value);
      template<>
      void SetValue(const char*&value);
      template<>
      void SetValue(void*& value);
      template<>
      void SetValue(std::string& value);

      METADLL_API void SetValueIndirection(void* value, int indirection);

      METADLL_API void SetOwns(bool owns);
      METADLL_API void SetType(Metadata* type);
      METADLL_API void SetData(void* data);

       template <typename Type>
      void Copy(const Type& type);

      METADLL_API void Invalidate();
      METADLL_API void Validate();

      METADLL_API bool IsValid();
      METADLL_API void* GetData();
      METADLL_API Metadata* GetMetadata();
      METADLL_API unsigned short GetIndirection();

      METADLL_API void SetLevelsOfIndirection(unsigned short indirection);

    private:
      bool owns_;
      void* data_;
      Metadata* type_;
      //Language origin;
      bool is_valid_;
      unsigned short levels_of_indirection_;
  };

}