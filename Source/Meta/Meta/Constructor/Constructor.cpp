#include "MetaPrecompiled.h"

#include "Constructor.h"

#include "MetaUtility.h"
#include "SimplifyType.h"

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
