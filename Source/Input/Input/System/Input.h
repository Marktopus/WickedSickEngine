#pragma once

#include "Core/CoreInterface.h"

#include "InputDLL.h"

namespace WickedSick
{
  struct InputBuffer;
  class InputHandler;
  class Input : public System
  {
  public:
    INPUTDLL_API Input();
    INPUTDLL_API ~Input();
    INPUTDLL_API void Initialize();
    INPUTDLL_API bool Load();
    INPUTDLL_API bool Reload();
    INPUTDLL_API void Update(float dt);
    INPUTDLL_API void UpdateInput(InputBuffer* buf);
    INPUTDLL_API void ReceiveMessage(Event * msg);

    INPUTDLL_API InputHandler* GetHandler();
  private:
    InputHandler* handler_;

  };
}
