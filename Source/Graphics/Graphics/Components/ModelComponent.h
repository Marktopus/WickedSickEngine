#pragma once

#include "Core/CoreInterface.h"
#include "GraphicsDLL.h"

namespace WickedSick
{
  class Model;
  class ModelComponent : public Component
  {
  public:
    GRAPHICSDLL_API ModelComponent( const std::string& model = "",
                                    GameObject* owner = nullptr);
    GRAPHICSDLL_API ~ModelComponent();
    GRAPHICSDLL_API std::string GetName();
    GRAPHICSDLL_API void Destroy();
    GRAPHICSDLL_API void SetModel(const std::string& model);
    GRAPHICSDLL_API void Initialize();
    GRAPHICSDLL_API void Update(float dt);
  private:
    const std::string name_;
    std::string model_;
    Model* base_;
  };
}
