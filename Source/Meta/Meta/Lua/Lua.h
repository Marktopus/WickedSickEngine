///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        1/21/2014
//Description: lua header file
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#ifndef SCRIPTING_H
#define SCRIPTINGH
#include "System.h"
#include "LuaIncludes.h"
//#include "vld.h"
typedef int (*lua_CFunction) (lua_State *L);

namespace WickedSick
{
  class Script;
  class ScriptManager;
  //in order to call a function from lua, we must be able to convert it to this type:
  typedef int (*lua_func) (lua_State *L, void *v);

  //THIS DOES NOT COME FROM LUA.
  struct luaL_MemberReg
  {
    const char* name;
    lua_func func;
    size_t offset;
  };
  
  class Lua : public System
  {
    public:
      MetaDef
      Lua();
      ~Lua();
      bool Load();
      Lua* Initialize();
      void Update(const float& dt);
      void ReceiveLetter(Letter*){}
      
      void UpdateInput();
      
      static int RefCast(lua_State* L);
      static int GetArgs(lua_State* L);
      static int Allocate(lua_State* L);
      static int GenericFunc(lua_State* L);
      static int GetMember(lua_State* L);
      static int access_member(lua_State* L, void* data, Marktopus::LuaMemberdata* memberData);


      Var* GetEngineRef(){return &engine_ref_;}
      lua_State* GetLua(){return lua_;}
      //this means that every function we want to call from lua, we must be able to 
      //represent in this form. So for every function we have, we'll have an 
      //equivalent that just takes a luastate and returns an int

      //so to call a function, we need to take all of the arguments off of
      //the lua stack, plug them into the function, then we call the function
      //and we push the return value back on to the stack
      Script* GetCurrentScript(){return (current_scripts_.size()) ? current_scripts_.back() : nullptr;}
      ScriptManager* GetScriptManager(){return manager_;}
      
      Script* GetScript(const std::string& filename);
      Script* AddScript(const std::string& filename);
      void RunScript(const std::string& filename);

      void set_current_script(Script* s)
      {
        current_scripts_.push_back(s);
      }

      void end_script()
      {
        current_scripts_.pop_back();
      }
    private:

      static void lua_heap_construct(LuaUserdata* data);

      static const std::string* find_constructor(lua_State* L, Metadata* type, std::vector<Var*>& args);
      
      static const char* find_type_name(lua_State* L);

      static const char* find_function_name(lua_State* L);

      static void construct(lua_State* L, const std::string& ctorName, Metadata* type, std::vector<Var*>& args, bool heap);

      static int call(lua_State *L);

      static void add(lua_State *L, std::vector<Marktopus::LuaMemberdata>& l);

      static int index_handler(lua_State *L);

      static int newindex_handler(lua_State *L);

      Var engine_ref_;
      ScriptManager* manager_;
      Script* current_script_;
      std::vector<Script*> current_scripts_;
      lua_State* lua_;
  };
}



#endif
