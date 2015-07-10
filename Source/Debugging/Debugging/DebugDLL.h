#pragma once
#ifdef DEBUGDLL_EXPORTS
#define DEBUGDLL_API __declspec(dllexport) 
#else
#define DEBUGDLL_API __declspec(dllimport) 
#endif
