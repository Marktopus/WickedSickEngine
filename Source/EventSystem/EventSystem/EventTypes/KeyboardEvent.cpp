#include "EventSystemPrecompiled.h"
#include "KeyboardEvent.h"

namespace WickedSick
{
  KeyboardMessage::KeyboardMessage( const std::string& key) : 
                                    Key(key),
                                    Event("KeyboardMessage", Event::Keyboard)
  {

  }
}
