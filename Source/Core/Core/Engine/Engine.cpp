#include "CorePrecompiled.h"
#include "Engine.h"

#include "System/SystemType.h"
#include "System/System.h"
#include "General/FrameController.h"

#include <thread>

#include "Utility/UtilityInterface.h"
#include "Debugging/DebugInterface.h"
namespace WickedSick
{
  
  Engine* Engine::Core = nullptr;

  COREDLL_API Engine::Engine() :  frame_controller_(nullptr),
                                  active_(true)
  {
    Core = this;
    systems_.resize(ST_Count, nullptr);
  }

  COREDLL_API Engine::~Engine()
  {
    for (auto& it : systems_)
    {
      if (it)
      {
        delete it;
      }
    }
  }

  COREDLL_API void Engine::AddSystem(System* sys)
  {
    systems_[sys->GetType()] = sys;
    sys->SetCore(this);
  }

  COREDLL_API System* Engine::GetSystem(SystemType type)
  {
    WSAssert((type < ST_Count) && (type > 0), "Unknown system type!");
    return systems_[type];
  }

  COREDLL_API std::vector<System*>& Engine::GetSystems()
  {
    return systems_;
  }

  COREDLL_API void Engine::Initialize()
  {
    frame_controller_ = new FrameController();
    for (auto& it : systems_)
    {
      if (it)
      {
        it->Initialize();
        //initThreads[it->GetType()] = new std::thread(&System::Initialize, it);
      }
    }
  }

  COREDLL_API void Engine::Load()
  {
    for (auto& it : systems_)
    {
      if (it && !it->Load())
      {
        ConsolePrint("System Failed to Load!");
        __debugbreak();
      }
    }
  }

  COREDLL_API void Engine::Reload()
  {
    for (auto& it : systems_)
    {
      if (it && !it->Reload())
      {
        ConsolePrint("System Failed to Reload!");
        __debugbreak();
      }
    }
  }

  COREDLL_API void Engine::Update()
  {
    frame_controller_->Update();
    for (auto& it : systems_)
    {
      if(it)
      {
        if (it->GetType() == ST_Physics)
        {
          while (frame_controller_->Step())
          {
            it->Update(frame_controller_->GetTimeStep());
          }
        }
        else
        {
          it->Update(frame_controller_->GetFrameTime());
        }
      }
    }
  }

  COREDLL_API bool Engine::IsActive()
  {
    return active_;
  }

  COREDLL_API void Engine::ShutDown()
  {
    active_ = false;
  }

}
