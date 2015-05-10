#include "CorePrecompiled.h"
#include "System.h"

namespace WickedSick
{
  COREDLL_API System::System(System::Type type) : type_(type),
                                                core_(nullptr)
  {

  }

  COREDLL_API System::~System()
  {

  }

  COREDLL_API void System::SetCore(Engine* core)
  {
    core_ = core;
  }

  COREDLL_API Engine* System::GetCore() const
  {
    return core_;
  }

  COREDLL_API System::Type System::GetType()
  {
    return type_;
  }
}

