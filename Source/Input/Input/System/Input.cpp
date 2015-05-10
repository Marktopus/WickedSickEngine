#include "InputPrecompiled.h"
#include "Input.h"

namespace WickedSick
{

  INPUTDLL_API Input::Input() : System(System::Input)
  {
  }

  INPUTDLL_API Input::~Input()
  {

  }

  INPUTDLL_API void Input::Initialize()
  {
  }
  
  INPUTDLL_API bool Input::Load()
  {
    return true;
  }
  
  INPUTDLL_API bool Input::Reload()
  {
    return true;
  }
  
  INPUTDLL_API void Input::Update(double dt)
  {
  }

  INPUTDLL_API void Input::ReceiveMessage()
  {
  }


}
