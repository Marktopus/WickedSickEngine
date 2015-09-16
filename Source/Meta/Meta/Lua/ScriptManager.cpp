///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        3/4/2014
//Description: ui list implementation
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#include "Precompiled.h"
#include "ScriptManager.h"
#include "Script.h"

namespace WickedSick
{
  ScriptManager::ScriptManager()
  {
    
  }

  ScriptManager::~ScriptManager()
  {
    for(auto it : scripts_)
    {
      delete it.second;
    }
  }

  void ScriptManager::LoadScripts()
  {
    std::vector<std::string> files = FilesByExtensionRecursive("Scripts", "lua");
    for(auto& it : files)
    {
      MakeScript(it);
    }
    for(auto it : scripts_)
    {
      it.second->Load();
    }
  }

  void ScriptManager::ReloadScripts()
  {
    for(auto it : scripts_)
    {
      it.second->Unload();
      it.second->Load();
    }
  }

  Script* ScriptManager::MakeScript(const std::string& file)
  {
    if(file.size())
    {
      scripts_[file] = new Script(file);
      return scripts_[file];
    }
    return nullptr;
  }

  Script* ScriptManager::GetScript(const std::string& name)
  {
    std::string standardSlashes = name;
    unsigned index = standardSlashes.find_first_of("\\");
    while (index != std::string::npos) 
    {
      standardSlashes[index] = '/';
      index = standardSlashes.find_first_of("\\");
    }
    

    auto it = scripts_.find(standardSlashes);
    if(it != scripts_.end())
    {
      return it->second;
    }
    return NULL;
  }

}
