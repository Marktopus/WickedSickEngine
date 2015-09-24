#pragma once
#include "Core/CoreInterface.h"
#include "Event/Event.h"
#include "EventSystemDLL.h"

struct ID3D11RenderTargetView;
namespace WickedSick
{
  
  class Event;
  class EventCallback;
  class EventSystem : public System
  {
  public:
    EVENTSYSTEMDLL_API EventSystem();
    EVENTSYSTEMDLL_API ~EventSystem();
    EVENTSYSTEMDLL_API void Initialize();
    EVENTSYSTEMDLL_API bool Load();
    EVENTSYSTEMDLL_API bool Reload();
    EVENTSYSTEMDLL_API void Update(float dt);

    //point is invalidated by next frame, only for initialization
    EVENTSYSTEMDLL_API Event* QueueEvent(const std::string& eventName);

    EVENTSYSTEMDLL_API void Register( const std::string& eventName,
                                      EventCallback callback);

    EVENTSYSTEMDLL_API void ReceiveMessage(Event * msg);



  private:

    EVENTSYSTEMDLL_API void FireEvents();

    HashMap<std::string, std::vector<EventCallback>> event_map_;
    std::vector<Event*> event_queue_;

    MemoryManager<Event> event_manager_;

  };
}
