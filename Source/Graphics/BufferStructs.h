#pragma once

#include "Math/MathInterface.h"

namespace WickedSick
{
  struct ObjectBuffer
  {
    Matrix4 model;
  };
  
  struct SceneBuffer
  {
    Matrix4 worldToClip;
    Matrix4 cameraPos;
    float globalAmbient;
  };

  struct LightBuffer
  {
    Vector3 pos;
    Vector3 dir;
    Vector4 colors[3]; //ambient, diffuse, specular
    float intensities[3] //ambient, diffuse, specular
    
  };
}
