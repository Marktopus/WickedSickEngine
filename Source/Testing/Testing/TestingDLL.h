#pragma once
#ifdef TESTINGDLL_EXPORTS
#define TESTINGDLL_API __declspec(dllexport) 
#else
#define TESTINGDLL_API __declspec(dllimport) 
#endif
