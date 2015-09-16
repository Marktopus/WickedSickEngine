#pragma once

#include "Math/MathInterface.h"

#include "Event/Event.h"

namespace WickedSick
{

  class MouseEvent : public Event
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

    EVENTSYSTEMDLL_API MouseEvent(const Vector2i& delta, 
                                  Type type,
                                  Button button = ButtonCount);
    EVENTSYSTEMDLL_API ~MouseEvent();
  private:
    Vector2i  mouse_delta_;
    Button    mouse_button_;
    Type      mouse_type_;
  };
}