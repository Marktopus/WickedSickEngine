#pragma once

#ifdef OBJECTFACTORYDLL_EXPORTS
#define OBJECTFACTORYDLL_API __declspec(dllexport) 
#else
#define OBJECTFACTORYDLL_API __declspec(dllimport) 
#endif
