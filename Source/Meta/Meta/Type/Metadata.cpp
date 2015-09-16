///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        1/21/2014
//Description: holds implementation for functions requiring specific includes
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#include "Precompiled.h"
//#include "Metadata.h"
#include "MetaManager.h"

Metadata::Metadata( const std::string& name, 
                    const std::string& Namespace, 
                    size_t size,
                    ValueType valType, 
                    bool built_in_type) : name_(name), 
                                          namespace_(Namespace),
                                          val_type_(valType),
                                          size_(size),
                                          built_in_type_(built_in_type),
                                          inherits_from_(nullptr)
{
  MetaManager::RegisterMeta(this);
}

Metadata::Metadata( const std::string& name, 
                    size_t size, 
                    ValueType valType,
                    bool built_in_type ) :  name_(name), 
                                            val_type_(valType),
                                            size_(size), 
                                            built_in_type_(built_in_type),
                                            inherits_from_(nullptr)
{
  MetaManager::RegisterMeta(this);
}

std::string Metadata::GetName() const
{
  return name_;
}

const size_t & Metadata::GetSize() const
{
  return size_;
}

void Metadata::AddMember(const Member & member)
{
  members_.insert(std::make_pair(member.GetName(), member));
  //members_[member.GetName()] = member;
}

void Metadata::AddMemberFunction(const Function & function, std::string name)
{
  member_functions_.insert(std::make_pair(name, function));
}

ValueType Metadata::GetValueType() const
{
  return val_type_;
}

Member * Metadata::GetMember(std::string name)
{
  auto it = members_.find(name);
  if (it != members_.end())
  {
    return &(*it).second;
  }
  return nullptr;
}

std::unordered_map<std::string, Member>& Metadata::GetMembers()
{
  return members_;
}


std::unordered_map<std::string, Function>& Metadata::GetMethods()
{
  return member_functions_;
}

std::unordered_map<std::string, Constructor>& Metadata::GetConstructors()
{
  return constructors_;
}

void Metadata::AddConversion(Metadata * type)
{
  conversions_[type->GetName()] = type;
}

bool Metadata::Converts(Metadata* type)
{
  if(type->GetEnumConstants().size())
  {
    type = FindType(int);
  }
  if(type != this)
  {
    auto it = conversions_.find(type->GetName());
    return it != conversions_.end();
  }
  return true;
}

bool Metadata::IsBuiltInType()
{
  return built_in_type_;
}

std::vector<luaL_Reg>& Metadata::GetLuaMethods()
{
  return lua_method_metatable_;
}

std::vector<luaL_Reg>& Metadata::GetLuaMetaMethods()
{
  return lua_metamethod_metatable_;
}

std::vector<Marktopus::LuaMemberdata>& Metadata::GetLuaGetters()
{
  return lua_getter_metatable_;
}

std::vector<Marktopus::LuaMemberdata>& Metadata::GetLuaSetters()
{
  return lua_setter_metatable_;
}

void Metadata::AddConstructor(std::string name, const Constructor & ctor)
{
  constructors_[name] = ctor;
}

std::set<Metadata*>& Metadata::GetDerived()
{
  return derived_;
}

void Metadata::AddDerived(Metadata * type)
{
  derived_.insert(type);
  type->inherits_from_ = this;
}

bool Metadata::InheritsFrom(Metadata * type)
{
  return inherits_from_ == type;
}

bool Metadata::BaseClassOf(Metadata * type)
{
  for (auto& it : derived_)
  {
    if (type == it)
    {
      return true;
    }
  }
  return false;
}

std::vector<const char*>& Metadata::GetEnumConstants()
{
  return enum_constants_;
}

RegisterType(,Metadata)
}
