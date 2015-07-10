#include "TestingPrecompiled.h"
#include "HashMapTests.h"

namespace WickedSick
{
  TESTINGDLL_API void HashMap_print(const HashMap<std::string, int>& map)
  {
    for (auto it : map)
    { 
     // ConsolePrint(it.key + std::to_string(it.type));
    }
  }

  TESTINGDLL_API bool HashMap_insert()
  {
    HashMap<std::string, int> map;
    for (int i = 0; i < 20; ++i)
    {
      map.insert(HashMap<std::string, int>::Entry("Hello" + std::to_string(i), i));
    }
    HashMap_print(map);
    return true;
  }
}