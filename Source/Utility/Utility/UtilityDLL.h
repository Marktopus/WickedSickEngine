#pragma once
#ifdef UTILITYDLL_EXPORTS
#define UTILITYDLL_API __declspec(dllexport) 
#else
#define UTILITYDLL_API __declspec(dllimport) 
#endif
