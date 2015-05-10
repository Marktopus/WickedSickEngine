#pragma once
#include "CoreDLL.h"
#include "System/System.h"
#include <vector>


namespace WickedSick
{
  //predeclarations
  class System;
  class FrameController;


  class Engine
  {
  public:
    COREDLL_API Engine();
    COREDLL_API ~Engine();
    COREDLL_API void AddSystem(System* sys);
    
    template <typename T>
    T* GetSystem(System::Type type)
    {
      return reinterpret_cast<T*>(systems_[type]);
    }

    COREDLL_API System* GetSystem(System::Type type);

    COREDLL_API void Initialize();
    COREDLL_API void Load();
    COREDLL_API void Reload();
    COREDLL_API void Update();

    COREDLL_API bool IsActive();
    COREDLL_API void ShutDown();

  private:
    std::vector<System*>  systems_;
    FrameController*      frame_controller_;
    bool                  active_;
  };
}
