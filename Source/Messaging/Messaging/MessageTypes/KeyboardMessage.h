#pragma once

#include "MessagingDLL.h"
#include "Message.h"

namespace WickedSick
{
  struct KeyboardMessage : public Message
  {
    MESSAGINGDLL_API KeyboardMessage( System::Type origin,
                                      System::Type destination,
                                      std::string key);
    std::string Key;
  };
}
