#pragma once

#ifdef _DEBUG
  #define WSAssert(condition, errorMessage) \
  if (!condition)                           \
  {                                         \
    ConsolePrint(errorMessage);             \
    throw(0);                               \
  }


#endif

#ifdef _RELEASE
  #define WSAssert(condition, errorMessage) \
  if (!condition)                           \
  {                                         \
    ConsolePrint(errorMessage);             \
  }
#endif
