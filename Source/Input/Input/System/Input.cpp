#include "InputPrecompiled.h"
#include "Input.h"
#include "Handlers/InputBuffer.h"
#include "Handlers/InputHandler.h"

#include "Imgui/include/imgui.h"

namespace WickedSick
{

  INPUTDLL_API Input::Input() : System(ST_Input)
  {
    handler_ = new InputHandler();
  }

  INPUTDLL_API Input::~Input()
  {

  }

  INPUTDLL_API void Input::Initialize()
  {
  }
  
  INPUTDLL_API bool Input::Load()
  {
    handler_->Load("nofile");
    return true;
  }
  
  INPUTDLL_API bool Input::Reload()
  {
    return true;
  }
  
  INPUTDLL_API void Input::Update(float dt)
  {
    handler_->Update(dt);
    
  }

  INPUTDLL_API void Input::ReceiveMessage(Event * msg)
  {
  }

  INPUTDLL_API void Input::UpdateInput(InputBuffer* buf)
  {
    handler_->UpdateInput(*buf);
  }

  INPUTDLL_API InputHandler* Input::GetHandler()
  {
    return handler_;
  }


}
