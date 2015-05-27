#include "UtilityPrecompiled.h"
#include "UtilityDLL.h"

#include <string>
#include <iostream>

namespace WickedSick
{

  UTILITYDLL_API std::string TrimSpaces(std::string toTrim)
  {
    for (auto& it = toTrim.begin() + 1; it != toTrim.end(); ++it)
    {
      if (*it == ' ' && *(it - 1) == ' ')
      {
        it = toTrim.erase(it);
      }
    }
    return toTrim;
  }
}