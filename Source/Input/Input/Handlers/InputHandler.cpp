
#include "InputPrecompiled.h"
#include "InputHandler.h"

namespace WickedSick
{
  INPUTDLL_API InputHandler::InputHandler() : active_(true),
                                              cur_wheel_pos_(0),
                                              current_modifiers_{false, false, false}
  {
    Key toadd;
    for(int i = 0; i < MaxKeys; ++i)
    {
      toadd.key = i;
      toadd.sinceReleased = 0.0f;
      for(int j = 0; j < InputType::Count; ++j)
      {
        toadd.inputType[j] = false;
      }
      keys.push_back(toadd);
    }
  }

  INPUTDLL_API void InputHandler::SetActive(bool active)
  {
    active_ = active;
  }

  INPUTDLL_API void InputHandler::Update(float dt)
  {
    for(int i = 0; i < MaxKeys; ++i)
    {
      if(!keys[i].inputType[InputType::Pressed])
      {
        keys[i].sinceReleased += dt;
      }
    }
  }

  INPUTDLL_API bool InputHandler::Check(const std::string & identifier)
  {
    return active_inputs_.find(identifier) != active_inputs_.end();
  }

  INPUTDLL_API Vector2i InputHandler::GetMousePos()
  {
    return cur_mouse_pos_;
  }

  INPUTDLL_API int InputHandler::GetScrollPos()
  {
    return cur_wheel_pos_;
  }

  INPUTDLL_API void InputHandler::UpdateInput(const InputBuffer & buf)
  {
    cur_mouse_pos_ = buf.mousePos;
    cur_wheel_pos_ = buf.wheelChange;
    memcpy(current_modifiers_, buf.current_modifiers_, sizeof(current_modifiers_));
    for(int i = 0; i < MaxKeys; ++i)
    {

      // if they were toggled now they're not
      if(keys[i].inputType[InputType::Toggled])
      {
        keys[i].inputType[InputType::Toggled] = false;
      }
      if(keys[i].inputType[InputType::DoubleToggled])
      {
        keys[i].inputType[InputType::DoubleToggled] = false;
      }
      if (buf.down[i])
      {
        if(!keys[i].inputType[InputType::Pressed])
        {
          keys[i].inputType[InputType::Toggled] = true;
          keys[i].inputType[InputType::Pressed] = true;
        }
        if(keys[i].sinceReleased < 0.5f)
        {
          keys[i].inputType[InputType::DoublePressed] = true;
          keys[i].inputType[InputType::DoubleToggled] = true;
        }
        keys[i].sinceReleased = 0.0f;
      }
      else
      {
        if(keys[i].inputType[InputType::DoublePressed])
        {
          keys[i].inputType[InputType::DoublePressed] = false;
        }
        if (keys[i].inputType[InputType::Pressed])
        {
          keys[i].inputType[InputType::Pressed] = false;
          keys[i].inputType[InputType::Released] = true;
        }
        else
        {
          keys[i].inputType[InputType::Released] = false;
        }
      }
    }
    bool pass;
    for(auto& input : inputs_)
    {
      pass = false;
      Keybind& keybind = input.val;
      if(keys[keybind.primaryId].inputType[keybind.type])
      {
        pass = true;
        std::set<int>& inputKeys = keybind.ids;
        for (auto& it : inputKeys)
        {
          pass = pass && keys[it].inputType[InputType::Pressed];
        }
        for(int i = 0; i < ModifierType::Count; ++i)
        {
          bool found = keybind.modifiers.find((ModifierType::Enum)i) != keybind.modifiers.end();
          pass = pass && (current_modifiers_[i] == found);
        }
      }
      if(pass)
      {
        if(!active_inputs_.empty())
        {
          for (auto& it : active_inputs_)
          {
            Keybind& otherKeybind = (*inputs_.find(it)).val;
            if (otherKeybind.primaryId == keybind.primaryId)
            {
              if ((keybind.ids.size() > otherKeybind.ids.size()) || (keybind.modifiers.size() > otherKeybind.modifiers.size()))
              {
                active_inputs_.erase(it);
                active_inputs_.insert(input.key);
                break;
              }
            }
          }
        }
        else
        {
          active_inputs_.insert(input.key);
        }
      }
      else if(active_inputs_.find(input.key) != active_inputs_.end())
      {
        active_inputs_.erase(input.key);
      }
      
    }
  }


  INPUTDLL_API void InputHandler::Load(const std::string& filename)
  {
    inputs_.insert("Rotate", { InputType::Pressed, VK_RBUTTON, std::set<int>{}, std::set<ModifierType::Enum>{}});
    inputs_.insert("Move", { InputType::Pressed, VK_RBUTTON, std::set<int>{}, std::set<ModifierType::Enum>{ModifierType::Control}});
    inputs_.insert("ZoomIn", { InputType::Pressed, VK_ADD, std::set<int>{}, std::set<ModifierType::Enum>{}});
    inputs_.insert("ZoomOut", { InputType::Pressed, VK_SUBTRACT, std::set<int>{}, std::set<ModifierType::Enum>{}});
    //Serialization::Deserialize(filename, GetMetaType(), this);
  }

  INPUTDLL_API void InputHandler::Save(const std::string& filename)
  {
    //Serialization::Serialize(filename, GetMetaType(), this);
  }
}
