#include "EventSystemPrecompiled.h"
#include "MouseEvent.h"

namespace WickedSick
{
  EVENTSYSTEMDLL_API MouseEvent::MouseEvent(const Vector2i& delta,
                                            Type type,
                                            Button button) 
                                            : mouse_delta_(delta),
                                              mouse_button_(button),
                                              mouse_type_(type),
                                              Event("MouseEvent", Event::Mouse)
  {

  }

  EVENTSYSTEMDLL_API MouseEvent::~MouseEvent()
  {

  }

}