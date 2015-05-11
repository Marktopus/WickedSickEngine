#include "MessagingPrecompiled.h"
#include "Message.h"

#include "System/Messaging.h"

namespace WickedSick
{
  Messaging* Message::messaging_system_;

  int Message::id_count_ = 0;

  MESSAGINGDLL_API Message::Message(System::Type origin, 
                                    System::Type destination, 
                                    Type type,
                                    int frame_delay,
                                    float time_delay) :
                                    origin_(origin),
                                    destination_(destination),
                                    msg_type_(type),
                                    msg_ID_(id_count_++),
                                    frame_delay_(frame_delay),
                                    time_delay_(time_delay)
  {
    
  }

  MESSAGINGDLL_API Message::~Message()
  {
    
  }


  MESSAGINGDLL_API bool Message::IsDelayed()
  {
    return (frame_delay_ > 0) || (time_delay_ > 0.0f);
  }

  MESSAGINGDLL_API void Message::UpdateDelay(double dt)
  {
    time_delay_ -= dt;
    --frame_delay_;
  }

}
