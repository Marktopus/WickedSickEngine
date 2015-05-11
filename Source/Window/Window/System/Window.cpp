#include "WindowPrecompiled.h"
#include "Window.h"

#include "Messaging/MessagingInterface.h"
#include "Core/System/System.h"

namespace WickedSick
{
  LRESULT CALLBACK WindowProc(HWND hWnd,
                              UINT message,
                              WPARAM wParam,
                              LPARAM lParam)
  {
    // sort through and find what code to run for the message given
    switch(message)
    {
        ///////////////////////////////////////////////////////////////////////////
      // Handle Cursor
      ///////////////////////////////////////////////////////////////////////////
      case WM_MOUSEMOVE:
      {
      
        //if(window_active_)
        //{
        Vector2i delta;

        MouseMessage mouse(System::Window, System::Input, delta, MouseMessage::ButtonCount, MouseMessage::Moved);

        //}
        break;
      }
      case WM_MOUSEWHEEL:
      {
        //if(window_active_)
        //{
        
        //}      
        break;
      }
      case WM_LBUTTONUP:
      {
        //Message mouse(System::Window, System::Input, Message::Mouse);
        //mouse.mouse_info_.button = MouseMessage::Left;
        break;
      }
      case WM_RBUTTONUP:
      {
        //Message mouse(System::Window, System::Input, Message::Mouse);
        //mouse.mouse_info_.button = MouseMessage::Right;
        break;
      }
      case WM_MBUTTONUP:
      {
        //Message mouse(System::Window, System::Input, Message::Mouse);
        //mouse.mouse_info_.button = MouseMessage::Middle;
        break;
      }
      case WM_LBUTTONDOWN:
      {
        //Message mouse(System::Window, System::Input, Message::Mouse);
        //mouse.mouse_info_.button = MouseMessage::Left;
        break;
      }
      case WM_RBUTTONDOWN:
      {
        //Message mouse(System::Window, System::Input, Message::Mouse);
        //mouse.mouse_info_.button = MouseMessage::Right;
        break;
      }
      case WM_MBUTTONDOWN:
      {
        //Message mouse(System::Window, System::Input, Message::Mouse);
        //mouse.mouse_info_.button = MouseMessage::Middle;
        break;
      }
      case WM_MOUSELEAVE: //this doesn't seem to do anything
      {
        Message mouse(System::Window, System::Input, Message::Mouse);
      
        break;
      }

      ///////////////////////////////////////////////////////////////////////////
      // Focus Messages
      ///////////////////////////////////////////////////////////////////////////
      case WM_KILLFOCUS:
      {
        //Engine::ENGINE->Pause();
        //sound
        //FMOD::ChannelGroup* master;
        //soundSys->GetSystem()->getMasterChannelGroup(&master);
        //soundSys->Pause();
        ////

        break;
      }
    
      case WM_SETFOCUS:
      {
        //sound
        //FMOD::ChannelGroup* master;
        //soundSys->GetSystem()->getMasterChannelGroup(&master);
        //master->setVolume(Engine::ENGINE->GetSettings()->sound.MasterVolume);
        //if(!Engine::ENGINE->IsPaused())
        //{
        //  soundSys->UnPause();
        //}
        ////
      


        break;
      }
    

      ///////////////////////////////////////////////////////////////////////////
      // Handle Keys
      ///////////////////////////////////////////////////////////////////////////
      case WM_KEYDOWN:
      {
        //if(window_active_)
        //{
          //Message keyboard(System::Window, System::Input, Message::Keyboard);      
          //keyboard.keyboard_info_.key = wParam;
        //}
        break;
      }
      case WM_KEYUP:
      {
        //if(data.m_window_active)
        //{
          //Message keyboard(System::Window, System::Input, Message::Keyboard);      
          //keyboard.keyboard_info_.key = wParam;
        //}
        break;
      }
      ///////////////////////////////////////////////////////////////////////////
      // Handle Resize
      ///////////////////////////////////////////////////////////////////////////
      case WM_SIZE:
      {
        //if(window->IsFullscreen())
        //{
        //  data.m_window_size = data.m_desktop_size;
        //  data.m_viewport_size = data.m_desktop_size;
        //}
        //else
        //{
        //  RECT wind = { 0, 0, data.m_target_size.x, 
        //                      data.m_target_size.y };
        //  if(GetClientRect(window->GetHandle(), &wind))
        //  {
        //    //adjust window for padding
        //    RECT correctW = { 0, 0, 
        //                      data.m_target_size.x, 
        //                      data.m_target_size.y };
        //    AdjustWindowRect(&correctW, WS_OVERLAPPEDWINDOW, FALSE); 
        //    int VPw = correctW.right - correctW.left;
        //    int VPh = correctW.bottom - correctW.top;
        //    data.m_window_size.Set(VPw, VPh);
        //  }
        //  else
        //  {
        //    //Failed to get client rect?

        //    data.m_renderable_window_size = data.m_target_size;

        //    //adjust window for padding
        //    RECT correctW = { 0, 0, 
        //                      data.m_target_size.x, 
        //                      data.m_target_size.y };
        //    AdjustWindowRect(&correctW, WS_OVERLAPPEDWINDOW, FALSE); 
        //    int VPw = correctW.right - correctW.left;
        //    int VPh = correctW.bottom - correctW.top;
        //    data.m_window_size.Set(VPw, VPh);
        //  }
        //}
        //window->ResizeD3D();
        break;
      }
      ///////////////////////////////////////////////////////////////////////////
      // Handle Destruction
      ///////////////////////////////////////////////////////////////////////////
      case WM_DESTROY:
      case WM_CLOSE:
      case WM_QUIT:
      {
        Message quit(System::Window, GlobalID, WickedSick::Message::Quit);
        
        return 0;
      }
      case WM_SYSKEYDOWN:
      {
        switch(wParam)
        {
          case VK_F4:
          {
            Message quit(System::Window, GlobalID, WickedSick::Message::Quit);
            return 0;         
          }
          case VK_RETURN:
          {
            //Message quit(System::Window, GlobalID, WickedSick::Message::Quit);
            break;
          }
          case VK_TAB:
          {
            //if(window->IsFullscreen())
            //{
              //ShowWindow(window->GetHandle(), SW_MINIMIZE);
            //}
            break;
          }
          default:
            break;
        }
        break;
      }
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
  }

  WINDOWDLL_API Window::Window() : System(System::Window)
  {
    window_instance_ = GetModuleHandle(nullptr);;
  }

  WINDOWDLL_API Window::~Window()
  {

  }

  WINDOWDLL_API void Window::Initialize()
  {

    //DefWindowProc(hwnd, uMsg, wParam, lParam);
    WNDCLASSEX windowInfo;
    ZeroMemory(&windowInfo, sizeof(windowInfo));
    
    windowInfo.cbSize = sizeof(windowInfo);
    windowInfo.style = CS_HREDRAW | CS_VREDRAW;
    windowInfo.lpfnWndProc = WindowProc;
    windowInfo.hInstance = window_instance_;
    windowInfo.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowInfo.hbrBackground = (HBRUSH)COLOR_WINDOW;
    windowInfo.lpszClassName = L"Classy";

    RegisterClassEx(&windowInfo);

    DEVMODE curMode, bestMode;
    curMode.dmSize = sizeof(curMode);
    int modeNumber = 0;
    
    int retVal;
    retVal = EnumDisplaySettings(NULL, modeNumber, &curMode);
    bestMode = curMode;

    while (retVal)
    {
      ++modeNumber;
      if (curMode.dmBitsPerPel >= bestMode.dmBitsPerPel)
      {
        if (  (curMode.dmPelsWidth  >= bestMode.dmPelsWidth ) &&
              (curMode.dmPelsHeight >= bestMode.dmPelsHeight)  )
        {
          bestMode = curMode;
        }
      }
      retVal = EnumDisplaySettings(NULL, modeNumber, &curMode);
    }

    window_size_.x = bestMode.dmPelsWidth;
    window_size_.y = bestMode.dmPelsHeight;

    std::lock_guard<std::mutex> handleLock(handle_mutex_);
    window_handle_ = CreateWindowEx(WS_EX_APPWINDOW,        //window type
                                    L"Classy",              //window class name?
                                    L"Wicked Sick Engine",  //window name
                                    WS_OVERLAPPEDWINDOW,    //also window type?
                                    0,                      //start position x
                                    0,                      //start position y
                                    bestMode.dmPelsWidth,   //width
                                    bestMode.dmPelsHeight,  //height
                                    nullptr,                //parent window ptr
                                    nullptr,                //menu ptr
                                    windowInfo.hInstance,   //got this from GetModuleHandle() earlier
                                    nullptr);               //used with multiple windows?
    ShowWindow(window_handle_, SW_SHOW);
  }
  
  WINDOWDLL_API bool Window::Load()
  {
    return true;
  }
  
  WINDOWDLL_API bool Window::Reload()
  {
    return true;
  }
  
  WINDOWDLL_API void Window::Update(double dt)
  {
    message_update();
  }

  WINDOWDLL_API void Window::ReceiveMessage(Message * msg)
  {

  }

  WINDOWDLL_API HWND& Window::GetWindowHandle()
  {
    return window_handle_;
  }


  WINDOWDLL_API std::mutex& Window::GetWindowHandleMutex()
  {
    return handle_mutex_;
  }

  WINDOWDLL_API Vector2i Window::GetWindowSize()
  {
    return window_size_;
  }


  void Window::message_update()
  {
    BOOL msgErr;
    do
    {
      msgErr = PeekMessage(&msg_, nullptr, 0, 0, PM_REMOVE);
      if (msgErr != -1)
      {
        switch (msg_.message)
        {
        default:
          break;
        }
        TranslateMessage(&msg_);
        DispatchMessage(&msg_);
      }
      else
      {
        //an error occurred?
        __debugbreak();
      }
    }
    while (msgErr);
  }
}
