#include "MessagingPrecompiled.h"
#include "Messaging.h"

#include "MessageTypes/StartupMessage.h"

namespace WickedSick
{
  MESSAGINGDLL_API Messaging::Messaging() : System(System::Messaging)
  {
    
  }

  MESSAGINGDLL_API Messaging::~Messaging()
  {

  }

  MESSAGINGDLL_API void Messaging::Initialize()
  {
    StartupMessage* startupMessage = new StartupMessage(this);
    startupMessage->Send();
  }

  MESSAGINGDLL_API bool Messaging::Load()
  {
    return true;
  }

  MESSAGINGDLL_API bool Messaging::Reload()
  {
    return true;
  }

  MESSAGINGDLL_API void Messaging::Update(double dt)
  {
  }

  MESSAGINGDLL_API void Messaging::QueueMessage(Message* message)
  {
    __debugbreak();
  }

  MESSAGINGDLL_API void Messaging::ReceiveMessage()
  {

  }
  

}
