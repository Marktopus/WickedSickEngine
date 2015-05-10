#pragma once

#include <string>
#include "Core/CoreDLL.h"

#include <utility>
#include <algorithm>

namespace WickedSick
{
  COREDLL_API void ConsolePrint(const std::string& contents);
  COREDLL_API std::string TrimSpaces(std::string toTrim);

  template <typename T>
  T clamp(const T& n, const T& lower, const T& upper) 
  {
    return std::max(lower, std::min(n, upper));
  }
}
