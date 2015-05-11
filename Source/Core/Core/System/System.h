#pragma once

#include "CoreDLL.h"

namespace WickedSick
{
  //predeclarations
  class Engine;
  class Message;
  class System
  {

    public:

      enum Type
      {
        #define RegisterSystem(x) x,
        #include "RegisterSystem.h"
        #undef RegisterSystem
        Count
      };

      COREDLL_API System(System::Type type);
      COREDLL_API ~System();
      COREDLL_API void SetCore(Engine* core);
      COREDLL_API Engine* GetCore() const;
      COREDLL_API System::Type GetType();
      virtual void  Initialize() = 0;
      virtual bool  Load() = 0;
      virtual bool  Reload() = 0;
      virtual void  Update(double dt) = 0;
      virtual void  ReceiveMessage(Message* msg) = 0;

      

    #define GlobalID System::Type::Count

    protected:
      System::Type  type_;
      Engine*       core_;
  };
}
