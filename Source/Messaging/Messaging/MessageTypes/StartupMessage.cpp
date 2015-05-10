#include "MessagingPrecompiled.h"

#include "StartupMessage.h"

namespace WickedSick
{
  MESSAGINGDLL_API StartupMessage::StartupMessage(Messaging* system) : 
                                          Message(System::Messaging, 
                                                  GlobalID, 
                                                  Message::Startup)
  {
    Message::messaging_system_ = system;
  }
}
