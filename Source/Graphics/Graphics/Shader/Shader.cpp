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
  Shader::Shader()
  {
  }

  Shader::~Shader()
  {
  }

  void Shader::SetShaders(const std::string& vert,
                          const std::string& pix,
                          const std::string& compute,
                          const std::string& geo)
  {
    if (!vert.empty())
    {
      vertex_file_ = vert;
    }
    if (!pix.empty())
    {
      pixel_file_ = pix;
    }
    if (!compute.empty())
    {
      compute_file_ = compute;
    }
    if (!geo.empty())
    {
      geometry_file_ = geo;
    }
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

}