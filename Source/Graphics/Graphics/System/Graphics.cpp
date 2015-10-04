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

#include <thread>
#include <mutex>


#include <direct.h>

namespace WickedSick
{
  GraphicsAPI*  Graphics::graphicsAPI  = nullptr;
  Factory<ModelComponent> Graphics::model_comp_factory_;
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
  }

  GRAPHICSDLL_API void Graphics::Initialize()
  {
    
    
    
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
    Model* cube = LoadModel("Content/Models/box.bin");
    Model* bunny = LoadModel("Content/Models/bunny.bin");
    Model* plane = LoadModel("Content/Models/plane.bin");
    Model* sphere = LoadModel("Content/Models/sphere.bin");


    cube->Initialize();
    bunny->Initialize();
    sphere->Initialize();
    plane->Initialize();

    Shader* shader = graphicsAPI->MakeShader();

    shader->SetShaders("Content/Shaders/Color/color.vs",
                       "Content/Shaders/Color/color.ps");
    shader->Initialize();
    shaders_.insert("Color", shader);
    

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

    int startOfName = modelName.find_last_of('/') + 1;
    if (startOfName == std::string::npos)
    {
      startOfName = modelName.find_last_of('\\') + 1;
      if (startOfName == std::string::npos)
      {
        startOfName = 0;
      }
    }
                                                              /*  size of name + extension        size of the extension*/
    std::string friendlyName = modelName.substr(startOfName, 
                                                (modelName.size() - startOfName) - (modelName.size() - dotIndex));
    

    if (modelLoader != loaders_.end())
    {
      newModel = ((*modelLoader).val)->Load(modelName);
      if (newModel)
      {
        models_.insert(friendlyName, newModel);
      }
    }
    else
    {
      ConsolePrint("Can't load file extension " + extension + " as model.");
    }
    return newModel;
  }

  GRAPHICSDLL_API void Graphics::RecompileShaders()
  {
    for (auto & it : shaders_)
    {
      it.val->Compile();
    }
  }
  
  GRAPHICSDLL_API void Graphics::Render()
  {
    mat_stack_->Push(camera_->GetViewMatrix());

    Matrix4 world;
    graphicsAPI->BeginScene();
    for (auto& shaderIt : shaders_)
    {
      Shader* shader = shaderIt.val;
      for (auto& modelIt : models_)
      {
        Model* model = modelIt.val;
        model->Render();
        for (auto& inst : model->GetInstances())
        {
          Transform* tr = (Transform*)inst->GetSibling(CT_Transform);

          world.Identity();



          Matrix4 rotate = world.GetRotatedXYZ(tr->GetRotation());
          Matrix4 scale = world.GetScaled(tr->GetScale());
          Matrix4 translate = world.GetTranslated(tr->GetPosition());

          world = translate * rotate * scale;

          
          


          //mat_stack_->Push(world);
          
          shader->Render(model->GetNumIndices(),
                         world,
                         projection_matrix_ * camera_->GetViewMatrix(),
                         camera_->GetPosition());

          //mat_stack_->Pop();
        }
      }
    }
    
    graphicsAPI->RenderScene();
    graphicsAPI->EndScene();
    mat_stack_->Pop();
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
