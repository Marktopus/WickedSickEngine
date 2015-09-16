#pragma once

#ifdef METADLL_EXPORTS
#define METADLL_API __declspec(dllexport) 
#else
#define METADLL_API __declspec(dllimport) 
#endif
