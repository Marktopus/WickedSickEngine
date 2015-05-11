#pragma once
#include "Core/CoreInterface.h"
#include "MessagingDLL.h"

struct ID3D11RenderTargetView;
namespace WickedSick
{
  struct Device;
  struct SwapChain;
  
  class Message;
  class Messaging : public System
  {
  public:
    MESSAGINGDLL_API Messaging();
    MESSAGINGDLL_API ~Messaging();
    MESSAGINGDLL_API void Initialize();
    MESSAGINGDLL_API bool Load();
    MESSAGINGDLL_API bool Reload();
    MESSAGINGDLL_API void Update(double dt);
    MESSAGINGDLL_API void QueueMessage(Message* message);
    MESSAGINGDLL_API void ReceiveMessage(Message * msg);

  private:

    std::vector<Message*> message_queue_;

  };
}
