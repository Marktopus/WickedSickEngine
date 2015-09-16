///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        3/4/2014
//Description: ui list implementation
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#include "Precompiled.h"
#include "LuaUserdata.h"

namespace WickedSick
{

#define DATA_LOC ((char*)this + sizeof(LuaUserdata))

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
/*
RegisterType(Marktopus, LuaString)
  RegisterMember(value);
}

RegisterType(Marktopus, LuaInt)
  RegisterMember(value);
}

RegisterType(Marktopus, LuaDouble)
  RegisterMember(value);
}

RegisterType(Marktopus, LuaBool)
  RegisterMember(value);
}

RegisterType(Marktopus, LuaFloat)
  RegisterMember(value);
}

RegisterType(Marktopus, LuaChar)
  RegisterMember(value);
}

RegisterType(Marktopus, LuaUnsigned)
  RegisterMember(value);
}

RegisterType(Marktopus, LuaLong)
  RegisterMember(value);
}

RegisterType(Marktopus, LuaShort)
  RegisterMember(value);
}
*/

