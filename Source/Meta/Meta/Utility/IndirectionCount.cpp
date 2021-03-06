#include "MetaPrecompiled.h"
#include "IndirectionCount.h"
namespace Reflection
{

  void * blind_dereference(void * ptr, int derefs)
  {
    if (derefs)
    {
      return blind_dereference(*reinterpret_cast<void**>(ptr), derefs - 1);
    }
    return ptr;
  }
}
