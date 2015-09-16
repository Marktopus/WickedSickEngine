#pragma once

#include "CoreDLL.h"

namespace WickedSick
{
  //predeclarations
  class Engine;
  class Event;


  enum SystemType
  {
    #define RegisterSystem(x) x,
    #include "RegisterSystem.h"
    #undef RegisterSystem
    ST_Count
  };

  class System
  {

    public:

      

      COREDLL_API System(SystemType type);
      COREDLL_API ~System();
      COREDLL_API void SetCore(Engine* core);
      COREDLL_API Engine* GetCore() const;
      COREDLL_API SystemType GetType();
      virtual void  Initialize() = 0;
      virtual bool  Load() = 0;
      virtual bool  Reload() = 0;
      virtual void  Update(double dt) = 0;
      virtual void  ReceiveMessage(Event* msg) = 0;

      

    #define GlobalID ST_Count

    protected:
      SystemType    type_;
      Engine*       core_;
  };
}
