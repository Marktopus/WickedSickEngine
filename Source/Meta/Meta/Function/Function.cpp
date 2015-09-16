#include "Precompiled.h"

Function::Function()
{
}

Function::~Function()
{
}

void Function::operator()(Var* object, Var* returnValue, std::vector<Var*> args)
{
  caller(function_, object, returnValue, args);
}
