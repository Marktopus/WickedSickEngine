#include "GraphicsPrecompiled.h"
#include "Shader.h"


//temp
#include "D3D/DXIncludes.h"
#include "API/DirectX.h"
#include "System/Graphics.h"
#include "D3D/SwapChain.h"
#include "D3D/Device.h"
#include "Buffer/Buffer.h"


namespace WickedSick
{
  Shader::Shader(const std::string& name,
                 ShaderCallback callback)
                  : name_(name),
                    callback_(callback)
  {
  
    vertex_file_ = "Content/Shaders/" + name_ + "/" + name_ + ".vs";
    pixel_file_ = "Content/Shaders/" + name_ + "/" + name_ + ".ps";

  }

  Shader::~Shader()
  {
  }

  Buffer * Shader::GetConstantBuffer(const std::string & name)
  {
    auto it = constant_buffers_.find(name);
    if(it != constant_buffers_.end())
    {
      return (*it).val;
    }
    return nullptr;
  }

  void Shader::AddConstantBuffer(Buffer * newBuf)
  {
    constant_buffers_.insert(newBuf->GetName(), newBuf);
  }

  void Shader::AddInstance(ModelComponent* comp)
  {
    auto it = instance_list_.find(comp->GetBase());
    if(it != instance_list_.end())
    {
      (*it).val.push_back(comp);
    }
    else
    {
      instance_list_.insert(comp->GetBase(), std::vector<ModelComponent*>{comp});
    }
    
  }

  void Shader::ClearInstances()
  {
    instance_list_.clear();
  }

  HashMap<Model*, std::vector<ModelComponent*>>& Shader::GetInstances()
  {
    return instance_list_;
  }

  std::string Shader::GetName() const
  {
    return name_;
  }

  void Shader::PrepareBuffers(ModelComponent* comp)
  {
    Graphics* graphics = (Graphics*)Engine::GetCore()->GetSystem(ST_Graphics);
    std::vector<ParamPasser> params;
    (*callback_)(graphics, comp, params);
    SetParameters(params);
    for(auto& it : params)
    {
      it.Release();
    }
  }

}