#include "GraphicsPrecompiled.h"
#include "GraphicsUtility.h"

#include "Graphics/DXIncludes.h"

#include "Core/CoreInterface.h"

namespace WickedSick
{
  void DXError(const HRESULT& retVal)
  {

      switch (retVal)
      {
      case DXGI_ERROR_DEVICE_HUNG:
        __debugbreak();
        break;
      case DXGI_ERROR_DEVICE_REMOVED:
        __debugbreak();
        break;
      case DXGI_ERROR_DEVICE_RESET:
        __debugbreak();
        break;
      case D3D11_ERROR_FILE_NOT_FOUND:
        __debugbreak();
        break;
      case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
        __debugbreak();
        break;
      case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
        __debugbreak();
        break;
      case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
        __debugbreak();
        break;
      case DXGI_ERROR_INVALID_CALL:
        __debugbreak();
        break;
      case DXGI_ERROR_WAS_STILL_DRAWING:
        __debugbreak();
        break;
      case E_FAIL:
        __debugbreak();
        break;
      case E_INVALIDARG:
        __debugbreak();
        break;
      case E_OUTOFMEMORY:
        __debugbreak();
        break;
      case E_NOTIMPL:
        __debugbreak();
        break;
      case S_FALSE:
        __debugbreak();
        break;
      case S_OK:
        break;
      default:
        __debugbreak();
        break;
        
      }
      auto errorCode = GetLastError();
      ConsolePrint("DirectX function call failed with error" + std::to_string(errorCode));

  }
}
