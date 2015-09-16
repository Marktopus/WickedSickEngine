#pragma once
#include "Core/CoreInterface.h"
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
    EVENTSYSTEMDLL_API void Update(double dt);
    EVENTSYSTEMDLL_API void QueueEvent(Event* message);

    EVENTSYSTEMDLL_API void Register( const std::string& eventName,
                                      const EventCallback& callback);

    EVENTSYSTEMDLL_API void ReceiveMessage(Event * msg);



  private:

    EVENTSYSTEMDLL_API void FireEvents();

    HashMap<std::string, std::vector<EventCallback>> event_map_;
    std::vector<Event*> event_queue_;

  };
}
