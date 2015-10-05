#include "GraphicsPrecompiled.h"
#include "Graphics.h"

#include "../D3D/Device.h"
#include "../D3D/SwapChain.h"

#include "Core/CoreInterface.h"
#include "Window/WindowInterface.h"

#include "API/DirectX.h"

#include "Camera/Camera.h"

#include "Model/Model.h"
#include "Shader/Shader.h"
#include "Model/Loaders/ObjLoader.h"
#include "Model/Loaders/BinLoader.h"


#include "Components/ModelComponent.h"

#include "Utility/UtilityInterface.h"

#include "Shader/ShaderCallbacks.h"

#include "ImGuiImpl/imgui_impl.h"

#include "Imgui/include/imgui.h"

#include <thread>
#include <mutex>

namespace WickedSick
{
  GraphicsAPI*  Graphics::graphicsAPI  = nullptr;
  GRAPHICSDLL_API Graphics::Graphics()  : camera_(nullptr),
                                          options_(nullptr),
                                          mat_stack_(nullptr),
                                          System(ST_Graphics)
  {
    loaders_.insert(".obj", new ObjLoader());
    loaders_.insert(".bin", new BinLoader());

    mat_stack_ = new MatrixStack();

    camera_ = new Camera();
    options_ = new GraphicsOptions();

    switch (options_->Api)
    {
      case OpenGLAPI:
        //shit aint happening right now
        WSError("Yeah no OpenGL support yet sorry");
        break;
      case DirectXAPI:
        graphicsAPI = new DirectX(); 
        break;
      default:
        WSError("What are you even what dude what. Whatever that is, we don't support it.");
        break;
    }
  }

  GRAPHICSDLL_API Graphics::~Graphics()
  {
    delete mat_stack_;
    delete camera_;
    delete options_;
    delete graphicsAPI;
    for(auto& it : loaders_)
    {
      delete (it.val);
    }
    //ImGui::Shutdown();
  }

  GRAPHICSDLL_API void Graphics::Initialize()
  {
    //ImGuiIO& io = ImGui::GetIO();
    //io.KeyMap[ImGuiKey_Tab] = VK_TAB;                              // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array that we will update during the application lifetime.
    //io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
    //io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
    //io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
    //io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
    //io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
    //io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
    //io.KeyMap[ImGuiKey_Home] = VK_HOME;
    //io.KeyMap[ImGuiKey_End] = VK_END;
    //io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
    //io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
    //io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
    //io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
    //io.KeyMap[ImGuiKey_A] = 'A';
    //io.KeyMap[ImGuiKey_C] = 'C';
    //io.KeyMap[ImGuiKey_V] = 'V';
    //io.KeyMap[ImGuiKey_X] = 'X';
    //io.KeyMap[ImGuiKey_Y] = 'Y';
    //io.KeyMap[ImGuiKey_Z] = 'Z';

    //io.RenderDrawListsFn = ImGui_RenderDrawLists;
    
    //ImGui::NewFrame();
    
    
    WickedSick::Window* window = core_->GetSystem<WickedSick::Window>(ST_Window);
    std::lock_guard<std::mutex> lk(window->GetWindowHandleMutex());

    graphicsAPI->Initialize(options_, window);

    // Setup the projection matrix.
    float fieldOfView = (float)PI / 2.0f;//90 degrees
    float screenAspect = (float)window->GetWindowSize().x / (float)window->GetWindowSize().y;

    // Create the projection matrix for 3D rendering.
    projection_matrix_.DoPerspective(90.0 * PI/180.0, 0.1f, 100000.0f, screenAspect);
    orthographic_matrix_.DoOrthographic(window->GetWindowSize().x, window->GetWindowSize().y, 0.1f, 100000.0f);
    camera_->SetPosition(0.0f, 0.0f, 0.0f);

    mat_stack_->Push(projection_matrix_);
  }

  GRAPHICSDLL_API bool Graphics::Load()
  {
    //temporary init
    LoadModel("box.bin");
    LoadModel("bunny.bin");
    LoadModel("sphere.bin");

    AddShader("color", &ColorShaderCallback);
    AddShader("wireframe", &WireframeShaderCallback);

    return true;
  }

  GRAPHICSDLL_API bool Graphics::Reload()
  {
    return true;
  }

  GRAPHICSDLL_API void Graphics::Update(float dt)
  {
    RecompileShaders();
    camera_->Orient(dt);
    Render();
  }

  GRAPHICSDLL_API void Graphics::ReceiveMessage(Event * msg)
  {

  }


  GRAPHICSDLL_API Model* Graphics::LoadModel(const std::string& modelName)
  {
    Model* newModel = nullptr;
    int dotIndex = modelName.find_last_of('.');
    std::string extension = modelName.substr(dotIndex, (modelName.size()) - dotIndex);
    auto& modelLoader = loaders_.find(extension);

    std::string friendlyName = modelName.substr(0, dotIndex);
    

    if (modelLoader != loaders_.end())
    {
      newModel = ((*modelLoader).val)->Load("Content/Models/" + modelName);
      if (newModel)
      {
        auto it = models_.find(friendlyName);
        if(it == models_.end())
        {
          models_.insert(friendlyName, newModel);
        }
        else
        {
          auto sit = models_.find(friendlyName + extension);
          if(sit == models_.end())
          {
            models_.insert(friendlyName + extension, newModel);
          }
          else
          {
            ConsolePrint("Two model files of same name and same type, cannot load model" + friendlyName + extension + "\n");
          }
          
        }
        
      }
    }
    else
    {
      ConsolePrint("Can't load file extension " + extension + " as model.\n");
    }
    newModel->Initialize();
    return newModel;
  }

  GRAPHICSDLL_API void Graphics::AddShader(const std::string& name, Shader::ShaderCallback callback)
  {
    Shader* shader = graphicsAPI->MakeShader(name, callback);
    shader->Initialize();
    shaders_.insert(shader->GetName(), shader);
  }

  GRAPHICSDLL_API void Graphics::RecompileShaders()
  {
    for (auto & it : shaders_)
    {
      it.val->Compile();
    }
  }

  GRAPHICSDLL_API void Graphics::BeginScene()
  {
    std::string shader;
    for(auto it : models_)
    {
      auto& modelInstances = it.val->GetInstances();
      for(auto& inst : modelInstances)
      {
        shader = inst->GetShader();
        auto shaderIt = shaders_.find(shader);
        if(shaderIt != shaders_.end())
        {
          (*shaderIt).val->AddInstance(inst);
        }
      }
    }
    graphicsAPI->BeginScene();
  }

  GRAPHICSDLL_API void Graphics::EndScene()
  {
    graphicsAPI->EndScene();
    for(auto it : shaders_)
    {
      it.val->ClearInstances();
    }
  }

  GRAPHICSDLL_API Matrix4 Graphics::GetProjection()
  {
    return projection_matrix_;
  }

  GRAPHICSDLL_API Shader * Graphics::GetShader(const std::string & name)
  {
    auto& shaderIt = shaders_.find(name);
    if(shaderIt != shaders_.end())
    {
      return (*shaderIt).val;
    }
    return nullptr;
  }

  GRAPHICSDLL_API Renderable * Graphics::GetRenderable(const std::string & name)
  {
    auto& renderableIt = renderables_.find(name);
    if(renderableIt != renderables_.end())
    {
      return &(*renderableIt).val;
    }
    return nullptr;
  }
  
  GRAPHICSDLL_API void Graphics::Render()
  {
    mat_stack_->Push(camera_->GetViewMatrix());

    Matrix4 modelToWorld;
    BeginScene();

    for(auto& shaderIt : shaders_)
    {
      Shader* shader = shaderIt.val;
      Model* model = nullptr;
      for(auto& modelIt : shader->GetInstances())
      {
        model = modelIt.key;
        model->Render();
        for(auto& inst : modelIt.val)
        {
          shader->PrepareBuffers(inst);
          shader->Render(model->GetNumIndices());
        }
      }
    }


    
    
    


    //ImGui::Render();

    EndScene();
    mat_stack_->Pop();
    //ImGui::NewFrame();
  }

  GRAPHICSDLL_API Camera * Graphics::GetCamera()
  {
    return camera_;
  }

  GRAPHICSDLL_API Model* Graphics::GetModel(const std::string& name)
  {
    auto& modelIt = models_.find(name);
    return (modelIt != models_.end()) ? (*modelIt).val : nullptr;
  }

}
