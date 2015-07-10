#include "Testing/TestingInterface.h"
#include "Testing/Tests/HashMapTests.h"

int TestDriver(void)
{
  WickedSick::Tester tester;

  tester.AddTest(&WickedSick::HashMap_insert, "HashMap");

  tester.RunAllTests();

  return 0;
}


