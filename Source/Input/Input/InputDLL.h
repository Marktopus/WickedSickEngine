#pragma once
#ifdef INPUTDLL_EXPORTS
#define INPUTDLL_API __declspec(dllexport) 
#else
#define INPUTDLL_API __declspec(dllimport) 
#endif
