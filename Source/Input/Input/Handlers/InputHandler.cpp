
#include "InputPrecompiled.h"
#include "InputHandler.h"

namespace WickedSick
{
  InputHandler::InputHandler(SystemType sys) :  active_(true),
                                                attached_sys_(sys)
  {
  }

  void InputHandler::SetActive(bool active)
  {
    active_ = active;
  }

  void InputHandler::Update()
  {
    //if(active_)
    //{
    //  Lua* luaSys = GET_SYSTEM(Lua);
    //  Script* inputScript = nullptr;
    //  if(attached_sys_ != ST_Count)
    //  {
    //    System* sys = Engine::ENGINE->GetSystemByType(attached_sys_);
    //    sys->UpdateInput();
    //    inputScript = luaSys->GetScript(sys->GetInputScript());
    //  }
    //  else
    //  {
    //    Engine::ENGINE->UpdateInput();
    //    inputScript = luaSys->GetScript(Engine::ENGINE->GetInputScript());
    //  }
    //  if(inputScript)
    //  {
    //    inputScript->Run();
    //  }
    //}
  }

  std::vector<Key> InputHandler::get_keys(const std::string& identifier)
  {
    std::vector<Key> keys;
    if(active_)
    {
      auto& iter = inputs_.find(identifier);
      if(iter != inputs_.end())
      {
        return iter->second;
      }
    }
    return keys;
  }

  bool InputHandler::IsToggled(const std::string& identifier)
  {
    //if(!active_)
    //{
    //  return false;
    //}
    //auto& keys = get_keys(identifier);
    //if(!keys.empty())
    //{
    //  Window* window = GET_SYSTEM(Window);
    //  for(auto& it = keys.begin(); it != keys.end() - 1; ++it)
    //  {
    //    if(!window->is_pressed(*it))
    //    {
    //      return false;
    //    }
    //  }
    //  if(!window->is_toggled(keys.back()))
    //  {
    //    return false;
    //  }
    //}
    //else
    //{
    //  return false;
    //}
    return true;
  }

  bool InputHandler::IsPressed(const std::string& identifier)
  {
    //if(!active_)
    //{
    //  return false;
    //}
    //auto& keys = get_keys(identifier);
    //Window* window = GET_SYSTEM(Window);
    //for(auto& it : keys)
    //{
    //  if(!window->is_pressed(it))
    //  {
    //    return false;
    //  }
    //}
    return true;
  }

  bool InputHandler::IsDoubleToggled(const std::string& identifier)
  {
    //if(!active_)
    //{
    //  return false;
    //}
    //auto& keys = get_keys(identifier);
    //if(!keys.empty())
    //{
    //  Window* window = GET_SYSTEM(Window);
    //  for(auto& it = keys.begin(); it != keys.end() - 1; ++it)
    //  {
    //    if(!window->is_pressed(*it))
    //    {
    //      return false;
    //    }
    //  }
    //  if(!window->is_doubletoggled(keys.back()))
    //  {
    //    return false;
    //  }
    //}
    //else
    //{
    //  return false;
    //}
    return true;
  }

  bool InputHandler::IsDoublePressed(const std::string& identifier)
  {
    //if(!active_)
    //{
    //  return false;
    //}
    //auto& keys = get_keys(identifier);
    //Window* window = GET_SYSTEM(Window);
    //for(auto& it : keys)
    //{
    //  if(!window->is_doubletapped(it))
    //  {
    //    return false;
    //  }
    //}
    return true;
  }


  void InputHandler::Load(const std::string& filename)
  {
    //Serialization::Deserialize(filename, GetMetaType(), this);
  }

  void InputHandler::Save(const std::string& filename)
  {
    //Serialization::Serialize(filename, GetMetaType(), this);
  }



}
