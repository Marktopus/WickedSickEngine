#include "EventSystemPrecompiled.h"
#include "EventSystem.h"

#include "Utility/UtilityInterface.h"

#include "Event/EventCallback.h"

#include "Event/Event.h"

namespace WickedSick
{
  EVENTSYSTEMDLL_API EventSystem::EventSystem() : System(ST_Messaging)
  {
    
  }

  EVENTSYSTEMDLL_API EventSystem::~EventSystem()
  {

  }

  EVENTSYSTEMDLL_API void EventSystem::Initialize()
  {
    
  }

  EVENTSYSTEMDLL_API bool EventSystem::Load()
  {
    return true;
  }

  EVENTSYSTEMDLL_API bool EventSystem::Reload()
  {
    return true;
  }

  EVENTSYSTEMDLL_API void EventSystem::Update(double dt)
  {
    FireEvents();
  }

  EVENTSYSTEMDLL_API void EventSystem::QueueEvent(Event* message)
  {
    event_queue_.push_back(message);
  }

  EVENTSYSTEMDLL_API void EventSystem::Register(const std::string & eventName,
                                                const EventCallback& callback)
  {
    auto it = event_map_.find(eventName);
    if (it != event_map_.end())
    {
      auto& callbackList = (*it).type;
      callbackList.push_back(callback);
    }
    else
    {
      event_map_.insert(eventName, std::vector<EventCallback>(1, callback));
    }
  }

  EVENTSYSTEMDLL_API void EventSystem::ReceiveMessage(Event * msg)
  {

  }

  EVENTSYSTEMDLL_API void EventSystem::FireEvents()
  {
    for (auto& it : event_queue_)
    {
      auto& mapIt = event_map_.find(it->GetName());
      auto& callbackList = (*mapIt).type;
      for (auto& cit : callbackList)
      {
        cit.Fire(it);
      }
    }
    event_queue_.clear();
  }
  

}
