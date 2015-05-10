#pragma once

#ifdef MATHDLL_EXPORTS
#define MATHDLL_API __declspec(dllexport) 
#else
#define MATHDLL_API __declspec(dllimport) 
#endif
