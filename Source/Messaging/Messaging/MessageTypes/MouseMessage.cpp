#include "MessagingPrecompiled.h"
#include "MouseMessage.h"

namespace WickedSick
{
  MESSAGINGDLL_API MouseMessage::MouseMessage(System::Type origin,
                                              System::Type destination,
                                              const Vector2i& delta,
                                              Button button,
                                              Type type) :
                                              mouse_delta_(delta),
                                              mouse_button_(button),
                                              mouse_type_(type),
                                              Message(origin, 
                                                      destination, 
                                                      Message::Mouse)
  {

  }

  MESSAGINGDLL_API MouseMessage::~MouseMessage()
  {

  }

}