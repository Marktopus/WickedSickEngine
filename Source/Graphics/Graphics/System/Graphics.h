#pragma once

#include "GraphicsDLL.h"

#include "API/GraphicsAPI.h"
#include "General/GraphicsOptions.h"
#include "Model/Model.h"


#include "Core/CoreInterface.h"
#include "Math/MathInterface.h"
#include "Components/ModelComponent.h"


#include "Utility/UtilityInterface.h"
struct ImDrawData;
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
    GRAPHICSDLL_API void Update(float dt);
    GRAPHICSDLL_API void ReceiveMessage(Event * msg);
    GRAPHICSDLL_API void Render();

    GRAPHICSDLL_API Camera* GetCamera();

    GRAPHICSDLL_API Model* GetModel(const std::string& name);
    GRAPHICSDLL_API Model* LoadModel(const std::string& model);

    GRAPHICSDLL_API void AddShader(const std::string& name, Shader::ShaderCallback callback);

    GRAPHICSDLL_API void RecompileShaders();

    GRAPHICSDLL_API void BeginScene();
    GRAPHICSDLL_API void EndScene();

    GRAPHICSDLL_API Matrix4 GetProjection();


    GRAPHICSDLL_API Buffer* GetUIVertexBuffer();
    GRAPHICSDLL_API Buffer* GetUIIndexBuffer();
    GRAPHICSDLL_API Shader* GetShader(const std::string& name);
    GRAPHICSDLL_API Renderable* GetRenderable(const std::string& name);
    
    static GraphicsAPI*            graphicsAPI;
  private:


    
    HashMap<int, ModelComponent*> model_components_; 
    HashMap<std::string, ModelLoader*> loaders_;
    HashMap<std::string, Model*> models_;
    HashMap<std::string, Renderable> renderables_;//basically buffers that don't have associated models
    HashMap<std::string, Shader*> shaders_;

    Matrix4 projection_matrix_;
    Matrix4 orthographic_matrix_;

    
    MatrixStack*      mat_stack_;

    Camera*           camera_;

    GraphicsOptions*  options_;


  };
}
