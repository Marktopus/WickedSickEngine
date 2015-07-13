#include "Testing/TestingInterface.h"
#include "Testing/Tests/HashMapTests.h"

int main(void)
{
  WickedSick::Tester tester;

  tester.AddTest(&WickedSick::HashMap_insert, "HashMap");
  tester.AddTest(&WickedSick::HashMap_insert_stress, "HashMap");
  tester.AddTest(&WickedSick::HashMap_erase, "HashMap");
  tester.AddTest(&WickedSick::HashMap_erase2, "HashMap");
  tester.AddTest(&WickedSick::HashMap_erase_stress, "HashMap");
  tester.AddTest(&WickedSick::HashMap_find, "HashMap");

  tester.RunAllTests();

  return 0;
}


