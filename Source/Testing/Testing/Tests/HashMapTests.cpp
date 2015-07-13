#include "TestingPrecompiled.h"
#include "HashMapTests.h"

namespace WickedSick
{
  TESTINGDLL_API void HashMap_print(const HashMap<std::string, int>& map)
  {
    for (auto it : map)
    { 
      ConsolePrint("[" + it.key + "]" + " = " + std::to_string(it.type));
      ConsolePrint("\n");
    }
    ConsolePrint("\n");
  }

  TESTINGDLL_API bool HashMap_insert()
  {
    HashMap<std::string, int> map;
    for (int i = 0; i < 20; ++i)
    {
      map.insert(HashMap<std::string, int>::Entry("Hello" + std::to_string(i), i));
      HashMap_print(map);
    }
    HashMap_print(map);
    return true;
  }

  TESTINGDLL_API bool HashMap_insert_stress()
  {
    HashMap<std::string, int> map;
    for (int i = 0; i < 2000; ++i)
    {
      map.insert(HashMap<std::string, int>::Entry("Hello" + std::to_string(i), i));
    }
    return (map.size() == 2000);
  }

  TESTINGDLL_API bool HashMap_erase()
  {
    HashMap<std::string, int> map;
    for (int i = 0; i < 20; ++i)
    {
      map.insert(HashMap<std::string, int>::Entry("Hello" + std::to_string(i), i));
    }

    for (int i = 0; i < 10; ++i)
    {
      map.erase("Hello" + std::to_string(i));
    }
    HashMap_print(map);

    return true;
  }

  TESTINGDLL_API bool HashMap_erase2()
  {
    HashMap<std::string, int> map2;
    for (int i = 0; i < 20; ++i)
    {
      map2.insert(HashMap<std::string, int>::Entry("Hello" + std::to_string(i), i));
    }

    for (int i = 0; i < 10; ++i)
    {
      map2.erase("Hello" + std::to_string(i));
    }

    for (int i = 0; i < 20; ++i)
    {
      map2.insert("Hello" + std::to_string(i + 20), i + 20);
    }

    for (int i = 0; i < 20; ++i)
    {
      map2.insert("Hello" + std::to_string(i), i);
    }

    for (int i = 0; i < 20; ++i)
    {
      map2.erase("Hello" + std::to_string(i));
    }
    HashMap_print(map2);
    return true;
  }

  TESTINGDLL_API bool HashMap_erase_stress()
  {
    HashMap<std::string, int> map;
    for (int i = 0; i < 2000; ++i)
    {
      map.insert("Hello" + std::to_string(i), i);
    }
    for (int i = 0; i < 2000; ++i)
    {
      map.erase("Hello" + std::to_string(i));
    }
    return (!map.size());
  }

  TESTINGDLL_API bool HashMap_find()
  {
    HashMap<std::string, int> map;
    for (int i = 0; i < 20; ++i)
    {
      map.insert("Hello" + std::to_string(i), i);
    }

    auto it = map.find("Hello0");
    (*it).type = 420;

    auto sit = map.find("Hello5");
    (*sit).type = 69;
    
    auto tit = map.find("Hello0");
    ConsolePrint((*tit).key + std::to_string((*tit).type));

    auto fit = map.find("Hello5");
    ConsolePrint((*fit).key + std::to_string((*fit).type));
    
    return true;
  }

}