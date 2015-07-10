#pragma once

#include "Utility/UtilityInterface.h"
#include "TestingDLL.h"
namespace WickedSick
{
  class UnitTest;
  typedef bool(*testerFn)(void);
  class Tester
  {
  public:

    TESTINGDLL_API Tester();

    TESTINGDLL_API void AddTest(UnitTest* newTest);

    TESTINGDLL_API void AddTest(testerFn test,
                 const std::string& category);

    TESTINGDLL_API bool RunTest(int testNumber);

    TESTINGDLL_API bool RunTestCategory(const std::string& category);

    TESTINGDLL_API bool RunAllTests();
  private:
    
    std::vector<UnitTest*> tests_;
    bool mem_check_;
    bool time_check_;
    bool silent_;

    MemoryManager<UnitTest> testManager;
  };
}
