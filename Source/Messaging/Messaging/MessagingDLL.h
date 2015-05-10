#pragma once

#ifdef MESSAGINGDLL_EXPORTS
#define MESSAGINGDLL_API __declspec(dllexport) 
#else
#define MESSAGINGDLL_API __declspec(dllimport) 
#endif
