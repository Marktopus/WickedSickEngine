#include "MetaPrecompiled.h"

#include "Constructor.h"

#include "Utility/MetaUtility.h"
#include "Utility/SimplifyType.h"
namespace Reflection
{
  Constructor::Constructor()
  {
  }

  Constructor::~Constructor()
  {
  }

  std::vector<Metadata*>& Constructor::GetArgs()
  {
    return args_;
  }

  void Constructor::operator()(Var* returnValue, std::vector<Var*> args)
  {
    caller(returnValue, args);
  }
}
