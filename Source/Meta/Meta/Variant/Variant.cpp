
#include "MetaPrecompiled.h"
#include "Variant.h"
#include "Type/Metadata.h"
#include "Type/MetaSingleton.h"
#include "Lua/LuaUserdata.h"
namespace Reflection
{

  METADLL_API Var::Var(void) 
            : levels_of_indirection_(0),
              is_valid_(false),
              type_(nullptr),
              data_(nullptr),
              owns_(false)
  {
  }

  METADLL_API Var::Var( Metadata * type,
            void * data) 
            : type_(type),
              data_(data),
              is_valid_(true),
              levels_of_indirection_(0),
              owns_(false)
  {
  }

  METADLL_API Var::Var(const Var& other) :  is_valid_(other.is_valid_),
                                type_(other.type_),
                                data_(other.data_),
                                levels_of_indirection_(other.levels_of_indirection_),
                                owns_(other.owns_)
  {
  }



  METADLL_API Var::Var(LuaUserdata* data) :  type_(data->GetType()),
                                                  is_valid_(true),
                                                  levels_of_indirection_(data->GetIndirection()),
                                                  data_(data->GetData()),
                                                  owns_(false)
  {

  }

  METADLL_API Var::~Var()
  {
    if(owns_)
    {
      delete[] reinterpret_cast<char*>(data_);
    }
  }

  METADLL_API void Var::SetValueIndirection(void * value, int indirection)
  {
    void* target = data_;
    //we want a pointer to our data, not the data itself
    int indirectionIt = levels_of_indirection_ + 1;


    while(indirection > indirectionIt)
    {
      value = *reinterpret_cast<void**>(value);
      --indirection;
    }

    while(indirection < indirectionIt)
    {
      target = *reinterpret_cast<void**>(target);
      --indirectionIt;
    }

    memcpy(target, value, (indirection > 1) ? sizeof(void*) : type_->GetSize());
  }

  METADLL_API void Var::SetOwns(bool owns)
  {
    owns_ = owns;
  }

  METADLL_API void Var::Invalidate()
  {
    is_valid_ = false;
  }

  METADLL_API void Var::SetType(Metadata * type)
  {
    type_ = type;
  }

  METADLL_API void Var::SetData(void * data)
  {
    data_ = data;
  }

  METADLL_API void Var::Validate()
  {
    is_valid_ = true;
  }

  METADLL_API bool Var::IsValid()
  {
    return is_valid_;
  }

  METADLL_API void* Var::GetData()
  {
    return data_;
  }

  METADLL_API Metadata* Var::GetMetadata()
  {
    return type_;
  }

  METADLL_API unsigned short Var::GetIndirection()
  {
    return levels_of_indirection_;
  }

  METADLL_API void Var::SetLevelsOfIndirection(unsigned short indirection)
  {
    levels_of_indirection_ = indirection;
  }

}

RegisterType(Reflection, Var)

}