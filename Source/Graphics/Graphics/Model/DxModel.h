#pragma once

#include "Model/Model.h"

namespace WickedSick
{
  class DxModel : public Model
  {
  public:
    DxModel();
    ~DxModel();
    void Initialize();
    void Render();
    
  private:
  };
}
