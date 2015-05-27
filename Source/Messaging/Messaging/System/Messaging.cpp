#include "MessagingPrecompiled.h"
#include "Messaging.h"

#include "Utility/UtilityInterface.h"

#include "Message.h"

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
    //for (auto msg : message_queue_)
    int i = 0;
    while (i < message_queue_.size())
    {
      if (message_queue_[i]->IsDelayed())
      {
        message_queue_[i]->UpdateDelay(dt);
        ++i;
      }
      else
      {
        auto& systemList = Engine::GetCore()->GetSystems();
        for (auto& sys : systemList)
        {
          if (sys)
          {
            sys->ReceiveMessage(message_queue_[i]);
          }
        }
        vector_remove(message_queue_, i);
      }
    }

  }

  MESSAGINGDLL_API void Messaging::QueueMessage(Message* message)
  {
    message_queue_.push_back(message);
  }

  MESSAGINGDLL_API void Messaging::ReceiveMessage(Message * msg)
  {

  }
  

}
