///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        1/21/2014
//Description: holds implementation for metadata class
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#ifndef METADATA_H
#define METADATAH

#include "Member.h"
#include "Function.h"
#include "Constructor.h"
#include "LuaUserdata.h"
#include "LuaIncludes.h"

class MetaManager;

enum ValueType
{
  ByReference,
  ByValue,
  ByPointer, //not sure if this is useful at all
  ByNone
};


enum Language
{
  FromLua,
  FromCPlusPlus,
  FromNone
};

class Metadata
{
  public:
    MetaDef;

    Metadata( const std::string& name, 
              const std::string& Namespace, 
              size_t size,
              ValueType valType = ByValue,
              bool built_in_type = false);

    Metadata( const std::string& name, 
              size_t size,
              ValueType valType = ByValue,
              bool built_in_type = false);

    void AddMember(const Member& member);
    void AddMemberFunction(const Function& function, std::string name);
    void AddConstructor(std::string name, const Constructor& ctor);
    void AddDerived(Metadata* type);

    std::string GetName() const;

    const size_t& GetSize() const;

    ValueType GetValueType() const;

    Member* GetMember(std::string name);

    std::set<Metadata*>& GetDerived();
    std::unordered_map<std::string, Member>& GetMembers();
    std::unordered_map<std::string, Function>& GetMethods();
    std::unordered_map<std::string, Constructor>& GetConstructors();
    
    std::vector<const char*>& GetEnumConstants();

    void AddConversion(Metadata* type);
    bool Converts(Metadata* type);

    bool IsBuiltInType();

    std::vector<luaL_Reg>& GetLuaMethods();
    std::vector<luaL_Reg>& GetLuaMetaMethods();

    std::vector<Marktopus::LuaMemberdata>& GetLuaGetters();
    std::vector<Marktopus::LuaMemberdata>& GetLuaSetters();


    bool InheritsFrom(Metadata* type);
    bool BaseClassOf(Metadata* type);

  private:
    std::string name_;
    std::string namespace_;

    ValueType   val_type_;

    Metadata* inherits_from_;
    std::set<Metadata*> derived_;

    std::vector<luaL_Reg> lua_method_metatable_;
    std::vector<luaL_Reg> lua_metamethod_metatable_;
    std::vector<Marktopus::LuaMemberdata> lua_getter_metatable_;
    std::vector<Marktopus::LuaMemberdata> lua_setter_metatable_;
    
    std::unordered_map<std::string, Metadata*> conversions_;
    std::unordered_map<std::string, Member> members_;
    std::unordered_map<std::string, Function> member_functions_;
    std::unordered_map<std::string, Constructor> constructors_;
    
    

    size_t size_;
    bool built_in_type_;
    std::vector<const char*> enum_constants_;
};

#endif
