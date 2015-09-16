#pragma once

#include "EventSystemDLL.h"
#include "Event/Event.h"

namespace WickedSick
{
  struct KeyboardMessage : public Event
  {
    EVENTSYSTEMDLL_API KeyboardMessage( const std::string & key);
    std::string Key;
  };
}
