#pragma once

#include "Core/CoreInterface.h"

#include "InputDLL.h"

namespace WickedSick
{

  class Input : public System
  {
  public:
    INPUTDLL_API Input();
    INPUTDLL_API ~Input();
    INPUTDLL_API void Initialize();
    INPUTDLL_API bool Load();
    INPUTDLL_API bool Reload();
    INPUTDLL_API void Update(double dt);
    INPUTDLL_API void Input::ReceiveMessage(Event * msg);
  private:


  };
}
