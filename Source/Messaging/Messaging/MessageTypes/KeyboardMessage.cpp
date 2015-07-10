#include "MessagingPrecompiled.h"
#include "KeyboardMessage.h"

namespace WickedSick
{
  KeyboardMessage::KeyboardMessage( System::Type origin,
                                    System::Type destination,
                                    std::string key) : 
                                    Key(key),
                                    Message(origin,
                                            destination,
                                            Message::Keyboard)
  {

  }
}
