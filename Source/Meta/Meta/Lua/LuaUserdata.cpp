
#include "MetaPrecompiled.h"
#include "LuaUserdata.h"
#include "Type/Metadata.h"
#include "Type/Member.h"

#define DATA_LOC ((char*)this + sizeof(Reflection::LuaUserdata))

namespace Reflection
{


  void LuaUserdata::SetMember(std::string name, void* value)
  {
    Member* member = type_->GetMember(name);
    memcpy(DATA_LOC + member->GetOffset(), (char*)value + member->GetOffset(), member->GetType()->GetSize());
  }

  void LuaUserdata::SetObject(Metadata* type, void* value)
  {
    memset(DATA_LOC, 0, (indirection_) ? sizeof(void*) : type->GetSize());
    memcpy(DATA_LOC, value, (indirection_) ? sizeof(void*) : type->GetSize());
    type_ = type;
  }

  void LuaUserdata::SetType(Metadata * type)
  {
    type_ = type;
  }


  void LuaUserdata::SetIndirection(unsigned ind)
  {
    indirection_ = ind;
  }

  unsigned LuaUserdata::GetIndirection()
  {
    return indirection_;
  }

  char* LuaUserdata::GetData()
  {
    return (char*)DATA_LOC;
  }

}

