#pragma once

#include "Message.h"

namespace WickedSick
{
  struct KeyboardMessage : public Message
  {
    char key;
  };
}