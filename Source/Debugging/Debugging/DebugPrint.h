#pragma once

#include <string>
#include "DebugDLL.h"
#include "DebugInterface.h"


namespace WickedSick
{
  enum ConsoleColor
  {
    ConsoleDarkBlue = 1,
    ConsoleGreen,
    ConsoleGrey,
    ConsoleDarkRed,
    ConsoleDarkPurple,
    ConsoleDarkBrown,
    ConsoleLightGrey,
    ConsoleDarkGrey,
    ConsoleBlue,
    ConsoleLimeGreen,
    ConsoleTeal,
    ConsoleRed,
    ConsolePurple,
    ConsoleYellow,
    ConsoleWhite
  };

  DEBUGDLL_API void ConsolePrint(const std::string& contents,
                                 ConsoleColor color = ConsoleWhite);
}
