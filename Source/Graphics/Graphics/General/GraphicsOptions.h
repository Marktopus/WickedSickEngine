#pragma once
#include "Math/MathInterface.h"
#include "API/APIType.h"

namespace WickedSick
{
  struct GraphicsOptions
  {
    GraphicsOptions(bool     vSync = false,
                    const Vector2i& resolution = Vector2i(1200, 720),
                    const Vector4&  clearColor = Vector4(0.1f, 0.1f, 0.1f, 1.0f),
                    APIType  api = DirectXAPI);


    bool            VSync;
    Vector2i        Resolution;
    Vector4         ClearColor;
    APIType         Api;

    //modifiable stuff goes here i.e.
    //int           shadowDetail;
    //int           antiAliasing;
    //int           textureDetail;
    //int           reflectionDetail;
    //bool          bloom;
    //LightingType  lighting;
  };
}