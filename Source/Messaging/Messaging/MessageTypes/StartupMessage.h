#pragma once

#include "Message.h"
#include "MessagingDLL.h"

namespace WickedSick
{
  class StartupMessage : public Message
  {
  public:
    MESSAGINGDLL_API StartupMessage(Messaging* system);
  };
}
