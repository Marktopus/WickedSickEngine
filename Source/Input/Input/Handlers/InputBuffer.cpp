///////////////////////////////////////////////////////////////////////////////
// Author(s)  : Mark
// Created    : 10/12/2014
// Description: 
// All Content © 2014 DigiPen (USA) Corporation, All Rights Reserved
///////////////////////////////////////////////////////////////////////////////
#include "InputPrecompiled.h"
#include "InputBuffer.h"


namespace WickedSick
{
  INPUTDLL_API Key::Key()
  {
    for(int i = 0; i < InputType::Count; ++i)
    {
      inputType[i] = false;
    }
  }

  INPUTDLL_API InputBuffer::InputBuffer() : current_modifiers_{false, false, false}, wheelChange(0)
  {
    memset(&down[0], 0, MaxKeys * sizeof(down[0]));
  }

  INPUTDLL_API bool InputBuffer::Get(int index)
  {
    if (index < MaxKeys)
    {
      return down[index];
    }
    return false;
  }

  INPUTDLL_API void InputBuffer::Set(int index, bool value)
  {
    if(index < MaxKeys)
    {
      down[index] = value;
    }

  }
}
