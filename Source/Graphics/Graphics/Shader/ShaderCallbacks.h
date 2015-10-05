#pragma once
#include "ParamTypeInfo.h"

class Graphics;
class ModelComponent;
namespace WickedSick
{
  void ColorShaderCallback(Graphics* gSys, ModelComponent* comp, std::vector<ParamPasser>& params);
  void WireframeShaderCallback(Graphics* gSys, ModelComponent* comp, std::vector<ParamPasser>& params);
}