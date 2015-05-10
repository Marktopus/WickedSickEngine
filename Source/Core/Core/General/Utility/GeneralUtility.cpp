#include "CorePrecompiled.h"
#include "GeneralUtility.h"

#include <string>
#include <iostream>

namespace WickedSick
{
  COREDLL_API void ConsolePrint(const std::string& contents)
  {
    std::cout << contents << std::endl;
  }

  COREDLL_API std::string TrimSpaces(std::string toTrim)
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