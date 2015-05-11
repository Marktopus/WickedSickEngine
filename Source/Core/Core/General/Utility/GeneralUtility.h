#pragma once

#include <string>
#include "Core/CoreInterface.h"

#include <utility>
#include <algorithm>
#include <vector>

namespace WickedSick
{
  COREDLL_API void ConsolePrint(const std::string& contents);
  COREDLL_API std::string TrimSpaces(std::string toTrim);

  template <typename T>
  T clamp(const T& n, const T& lower, const T& upper) 
  {
    return std::max(lower, std::min(n, upper));
  }

  template<typename T>
  void vector_remove(std::vector<T> container, int toRemove)
  {
    std::swap(container[toRemove], container[container.size() - 1]);
    container.pop_back();
  }
}
