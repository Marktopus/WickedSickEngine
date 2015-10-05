#pragma once
#include "Shader/ParamTypeInfo.h"
#include "Shader/Shader.h"

namespace WickedSick
{
  
  class Model;
  class Shader;
  struct GraphicsOptions;
  class Window;
  class Shader;
  enum APIType;


  class GraphicsAPI
  {
  public:

    GraphicsAPI(APIType api);
    virtual ~GraphicsAPI();

    virtual void Initialize(GraphicsOptions* options,
                            Window* window) = 0;
    virtual void CleanUp() = 0;

    virtual void BeginScene() = 0;
    virtual void EndScene() = 0;

    virtual Model* MakeModel() = 0;
    virtual Shader* MakeShader(const std::string& name, Shader::ShaderCallback callback) = 0;
    
  protected:
    GraphicsOptions* options_;

    virtual void clear_buffers() = 0;
    APIType api_;

  };
}
