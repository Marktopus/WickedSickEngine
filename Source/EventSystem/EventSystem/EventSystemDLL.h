#pragma once

#ifdef EVENTSYSTEMDLL_EXPORTS
#define EVENTSYSTEMDLL_API __declspec(dllexport) 
#else
#define EVENTSYSTEMDLL_API __declspec(dllimport) 
#endif
