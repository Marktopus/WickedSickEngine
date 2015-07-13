#pragma once

#include "Utility/UtilityInterface.h"
#include "Testing/TestingDLL.h"
#include "Debugging/DebugInterface.h"

namespace WickedSick
{

  TESTINGDLL_API void HashMap_print(const HashMap<std::string, int>& map);

  TESTINGDLL_API bool HashMap_insert();
  TESTINGDLL_API bool HashMap_insert_stress();

  TESTINGDLL_API bool HashMap_erase();
  TESTINGDLL_API bool HashMap_erase2();
  TESTINGDLL_API bool HashMap_erase_stress();
  
  TESTINGDLL_API bool HashMap_find();
}
