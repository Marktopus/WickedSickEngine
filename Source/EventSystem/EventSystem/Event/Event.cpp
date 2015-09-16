#include "EventSystemPrecompiled.h"
#include "Event.h"

#include "System/EventSystem.h"

namespace WickedSick
{
  EventSystem* Event::event_system_;

  int Event::id_count_ = 0;

  EVENTSYSTEMDLL_API Event::Event(const std::string& name, Type type) 
                                  : event_type_(type),
                                    event_name_(name),
                                    event_ID_(id_count_++)
  {
    
  }

  EVENTSYSTEMDLL_API std::string Event::GetName()
  {
    return event_name_;
  }

  EVENTSYSTEMDLL_API Event::~Event()
  {
    
  }

}
