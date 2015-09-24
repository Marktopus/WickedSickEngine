#include "EventSystemPrecompiled.h"
#include "EventSystem.h"

#include "Utility/UtilityInterface.h"

#include "Event/EventCallback.h"
#include "Event/EventCallbackList.h"

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
    //register engine wide events

    Register("Quit", QuitEvent);
  }

  EVENTSYSTEMDLL_API bool EventSystem::Load()
  {
    return true;
  }

  EVENTSYSTEMDLL_API bool EventSystem::Reload()
  {
    return true;
  }

  EVENTSYSTEMDLL_API void EventSystem::Update(float dt)
  {
    FireEvents();
  }


  EVENTSYSTEMDLL_API Event* EventSystem::QueueEvent(const std::string& eventName)
  {
    Event* newEvent = event_manager_.New(eventName);
    event_queue_.push_back(newEvent);
    return newEvent;
  }

  EVENTSYSTEMDLL_API void EventSystem::Register(const std::string & eventName,
                                                EventCallback callback)
  {
    auto it = event_map_.find(eventName);
    if (it != event_map_.end())
    {
      auto& callbackList = (*it).val;
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
      if(mapIt != event_map_.end())
      {
        auto& callbackList = (*mapIt).val;
        for (auto& cit : callbackList)
        {
          cit.Fire(it);
        }
      }
    }
    event_queue_.clear();
  }
  

}
