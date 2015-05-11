#pragma once

#include "Core/CoreInterface.h"

#include "MessagingDLL.h"

namespace WickedSick
{

  class Messaging;

  class Message
  {
  public:
    enum Type
    {
      #define RegisterType(x) x,
      #include "RegisterMessageType.h"
      #undef RegisterType
      Count
    };
    

    MESSAGINGDLL_API Message(System::Type origin, 
                             System::Type destination, 
                             Type type,
                             int frame_delay = 0,
                             float time_delay = 0.0f);
    MESSAGINGDLL_API virtual ~Message();

    //todo

    MESSAGINGDLL_API bool IsDelayed();
    MESSAGINGDLL_API void UpdateDelay(double dt);
    MESSAGINGDLL_API void SetDelay(int delay);
    MESSAGINGDLL_API void SetDelay(float delay);


  private:
    System::Type      origin_;
    System::Type      destination_;
    Type              msg_type_;
    int               msg_ID_;
    
    int               frame_delay_;
    float             time_delay_;

    static int        id_count_;

  protected:

    static Messaging* messaging_system_;

    

  };
}
