#pragma once

#ifdef WINDOWDLL_EXPORTS
#define WINDOWDLL_API __declspec(dllexport) 
#else
#define WINDOWDLL_API __declspec(dllimport) 
#endif
