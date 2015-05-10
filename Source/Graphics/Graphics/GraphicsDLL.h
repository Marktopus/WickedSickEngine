#pragma once

#ifdef GRAPHICSDLL_EXPORTS
#define GRAPHICSDLL_API __declspec(dllexport) 
#else
#define GRAPHICSDLL_API __declspec(dllimport) 
#endif
