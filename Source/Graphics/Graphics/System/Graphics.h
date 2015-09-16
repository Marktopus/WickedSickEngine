#pragma once

#include "GraphicsDLL.h"

#include "API/GraphicsAPI.h"
#include "General/GraphicsOptions.h"
#include "Model/Model.h"


#include "Core/CoreInterface.h"
#include "Math/MathInterface.h"
#include "Components/ModelComponent.h"


#include "Utility/UtilityInterface.h"

namespace WickedSick
{
  class ModelComponent;
  class MatrixStack;
  class Shader;
  class Model;
  class ModelLoader;
  class Camera;
  struct Device;
  struct SwapChain;
  

  class Graphics : public System
  {
  public:
    GRAPHICSDLL_API Graphics();
    GRAPHICSDLL_API ~Graphics();
    GRAPHICSDLL_API void Initialize();
    GRAPHICSDLL_API bool Load();
    GRAPHICSDLL_API bool Reload();
    GRAPHICSDLL_API void Update(double dt);
    GRAPHICSDLL_API void ReceiveMessage(Event * msg);
    GRAPHICSDLL_API void Render();

    GRAPHICSDLL_API Model* GetModel(const std::string& name);
    GRAPHICSDLL_API Model* LoadModel(const std::string& model);

    GRAPHICSDLL_API void RecompileShaders();

    
    static GraphicsAPI*            graphicsAPI;
  private:


    static Factory<ModelComponent> model_comp_factory_;
    
    HashMap<int, ModelComponent*> model_components_; 
    HashMap<std::string, ModelLoader*> loaders_;
    HashMap<std::string, Model*> models_;
    HashMap<std::string, Shader*> shaders_;

    Matrix4 projection_matrix_;
	  Matrix4 orthographic_matrix_;

    
    MatrixStack*      mat_stack_;

    Camera*           camera_;

    GraphicsOptions*  options_;

  };
}
