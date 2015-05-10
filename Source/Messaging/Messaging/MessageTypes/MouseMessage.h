#pragma once

#include "Math/MathInterface.h"

#include "Message.h"

namespace WickedSick
{

  class MouseMessage : public Message
  {
  public:
    enum Button
    {
      Left,
      Right,
      Middle,
      M1,
      M2,
      ButtonCount
    };
    enum Type
    {
      Moved,
      Pressed,
      Released,
      Entered,
      Exited,
      Clicked,
      DoubleClicked,
      Scrolled,
      TypeCount
    };

    MESSAGINGDLL_API MouseMessage(System::Type sender, 
                                  System::Type destination,
                                  const Vector2i& delta, 
                                  Button button, 
                                  Type type);
    MESSAGINGDLL_API ~MouseMessage();
  private:
    Vector2i  mouse_delta_;
    Button    mouse_button_;
    Type      mouse_type_;
  };
}