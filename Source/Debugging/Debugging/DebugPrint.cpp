#include "DebugPrecompiled.h"
#include "DebugDLL.h"
#include "DebugPrint.h"

#include "windows.h"

#include <string>
#include <iostream>

namespace WickedSick
{

  DEBUGDLL_API void ConsolePrint(const std::string& contents,
                                 ConsoleColor color)
  {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    std::cout << contents;
  }
}
