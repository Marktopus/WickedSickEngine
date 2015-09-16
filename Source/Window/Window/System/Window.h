#pragma once

#include "Core/CoreInterface.h"

#include "Math/MathInterface.h"

#include "Window/WindowDLL.h"
#include "Window/General/WindowSettings.h"

#include <mutex>

//#include <windows.h>
namespace WickedSick
{
  LRESULT CALLBACK WindowProc(HWND hWnd,
                              UINT message,
                              WPARAM wParam,
                              LPARAM lParam);

  class Window : public System
  {
  public:
    WINDOWDLL_API Window();
    WINDOWDLL_API ~Window();
    WINDOWDLL_API void Initialize();
    WINDOWDLL_API bool Load();
    WINDOWDLL_API bool Reload();
    WINDOWDLL_API void Update(double dt);
    WINDOWDLL_API void ReceiveMessage(Event * msg);
    WINDOWDLL_API HWND& GetWindowHandle();

    WINDOWDLL_API Vector2i GetWindowSize();


    WINDOWDLL_API std::mutex& GetWindowHandleMutex();
  private:

    void message_update();


    Vector2i window_size_;
    

    MSG msg_;
    HWND window_handle_;
    HINSTANCE window_instance_;

    std::mutex handle_mutex_;

    WindowSettings settings_;
  };
}
