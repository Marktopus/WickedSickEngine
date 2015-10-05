#include "GraphicsPrecompiled.h"
#include "DxShader.h"
#include "D3D/DXIncludes.h"
#include "API/DirectX.h"
#include "System/Graphics.h"
#include "D3D/SwapChain.h"
#include "D3D/Device.h"
#include "General/GraphicsUtility.h"
#include "Buffer/DxBuffer.h"
#include <filesystem>

namespace WickedSick
{

  DxShader::DxShader(const std::string& name,
                     ShaderCallback callback) : vertex_shader_(nullptr),
                                                pixel_shader_(nullptr),
                                                compute_shader_(nullptr),
                                                geometry_shader_(nullptr),
                                                layout_(nullptr),
                                                Shader(name, callback)
  {

  }
  
  DxShader::~DxShader()
  {

  }

  void DxShader::Initialize()
  {

    if (!Compile(true))
    {
      ConsolePrint("One or more shaders failed to compile.\n");
    }
    else
    {
      ReflectBuffers();
    }


  }

  void DxShader::SetParameters(const std::vector<ParamPasser>& params)
  {
    if(!pixel_shader_ || !vertex_shader_)
    {
      return;
    }
    DirectX* dx = reinterpret_cast<DirectX*>(Graphics::graphicsAPI);
    SwapChain* swapChain = dx->GetSwapChain();
    ID3D11DeviceContext* context = swapChain->device->D3DContext;


    for(auto& it : params)
    {
      auto& bufIt = constant_buffers_.find(it.Buffer);
      if(bufIt != constant_buffers_.end())
      {
        DxBuffer* buf = (DxBuffer*)(*bufIt).val;
        buf->SetParameter(it.Name, it.Data);
      }
    }

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    DxBuffer* buffer;
    std::vector<ID3D11Buffer*> bufferList;
    ID3D11Buffer* curBuf = nullptr;
    for(auto cbIt : constant_buffers_)
    {
      buffer = (DxBuffer*) cbIt.val;
      curBuf = (ID3D11Buffer*) buffer->BufferPointer();
      DXError(context->Map(curBuf,
                           0,
                           D3D11_MAP_WRITE_DISCARD,
                           0,
                           &mappedResource));

      memcpy(mappedResource.pData, buffer->GetData(), buffer->GetSize());
      context->Unmap(curBuf, 0);

      bufferList.push_back((ID3D11Buffer*)buffer->BufferPointer());
    }

    context->VSSetConstantBuffers(0, bufferList.size(), &bufferList[0]);
  }

  void DxShader::RenderShader(int indexCount)
  {
    DirectX* dx = reinterpret_cast<DirectX*>(Graphics::graphicsAPI);
    SwapChain* swapChain = dx->GetSwapChain();
    ID3D11DeviceContext* context = swapChain->device->D3DContext;
    context->IASetInputLayout(layout_);

    // Set the vertex and pixel shaders that will be used to render this triangle.
    context->VSSetShader(vertex_shader_, NULL, 0);
    context->PSSetShader(pixel_shader_, NULL, 0);

    // Render the triangle.
    context->DrawIndexed(indexCount, 0, 0);

    
  }


  bool DxShader::Compile(bool forceCompile)
  {
    DirectX* dx = reinterpret_cast<DirectX*>(Graphics::graphicsAPI);
    SwapChain* swapChain = dx->GetSwapChain();
    ID3D11Device* device = swapChain->device->D3DDevice;

    ID3D10Blob* errorMessage = nullptr;
    ID3D10Blob* vertexShaderBuffer = nullptr;
    ID3D10Blob* pixelShaderBuffer = nullptr;
    
    std::string baseFileName = vertex_file_.Path();
    std::wstring fileStr(baseFileName.begin(), baseFileName.end());
    if (vertex_file_.WasModified() || forceCompile)
    {
      while (!vertex_file_.Writable())
      {
        Sleep(1);
      }
      DXError(D3DCompileFromFile (fileStr.c_str(),
                                  NULL, 
                                  NULL, 
                                  "main",
                                  "vs_5_0",
                                #ifdef _DEBUG
                                  D3D10_SHADER_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 
                                #elif _RELEASE
                                  D3D10_SHADER_ENABLE_STRICTNESS,
                                #endif
                                  0, 
                                  &vertexShaderBuffer, 
                                  &errorMessage));
      if (errorMessage)
      {
        //error?
        if (vertexShaderBuffer)
        {
          vertexShaderBuffer->Release();
        }
        ConsolePrint("Shader Error: ");
        ConsolePrint((char*)errorMessage->GetBufferPointer());
        std::string filename(fileStr.begin(), fileStr.end());
        ConsolePrint("\n in shader " + filename + "\n");
        errorMessage->Release();
        return false;
      }
      if (vertex_shader_)
      {
        vertex_shader_->Release();
      }
      DXError(device->CreateVertexShader( vertexShaderBuffer->GetBufferPointer(), 
                                          vertexShaderBuffer->GetBufferSize(), 
                                          NULL, 
                                          &vertex_shader_));
      InitLayout(vertexShaderBuffer);
      vertexShaderBuffer->Release();
    }
    
    if (pixel_file_.WasModified() || forceCompile)
    {
      while (!pixel_file_.Writable())
      {
        Sleep(1);
      }
      baseFileName = pixel_file_.Path();
      fileStr = std::wstring(baseFileName.begin(), baseFileName.end());
      DXError(D3DCompileFromFile (fileStr.c_str(),
                                  NULL, 
                                  NULL, 
                                  "main", 
                                  "ps_5_0",
                                #ifdef _DEBUG
                                  D3D10_SHADER_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
                                #elif _RELEASE
                                  D3D10_SHADER_ENABLE_STRICTNESS,
                                #endif
                                  0, 
                                  &pixelShaderBuffer, 
                                  &errorMessage));
      if (errorMessage)
      {
        if (pixelShaderBuffer)
        {
          pixelShaderBuffer->Release();
        }
        ConsolePrint("Shader Error: ");
        ConsolePrint((char*)errorMessage->GetBufferPointer());
        std::string filename(fileStr.begin(), fileStr.end());
        ConsolePrint("\n in shader " + filename + "\n");
        errorMessage->Release();
        return false;
      }
      if (pixel_shader_)
      {
        pixel_shader_->Release();
      }
      DXError(device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),  
                                        pixelShaderBuffer->GetBufferSize(),   
                                        NULL, 
                                        &pixel_shader_));
      pixelShaderBuffer->Release();

    }
    return true;
  }

  void DxShader::ReflectBuffers()
  {

  }

  //DXGI_FORMAT find_param_type(const ShaderParam& param)
  //{
  //  switch (param.inputType)
  //  {
  //    case DataType::Int:
  //    {
  //      switch (param.size)
  //      {
  //        case sizeof(int) * 4:
  //          return DXGI_FORMAT_R32G32B32A32_SINT;
  //        case sizeof(int) * 3:
  //          return DXGI_FORMAT_R32G32B32_SINT;
  //        case sizeof(int) * 2:
  //          return DXGI_FORMAT_R32G32_SINT;
  //        case sizeof(int):
  //          return DXGI_FORMAT_R32_SINT;
  //        default:
  //          break;
  //      }
  //    }
  //    case DataType::Float:
  //    {
  //      switch (param.size)
  //      {
  //        case sizeof(float) * 4:
  //          return DXGI_FORMAT_R32G32B32A32_FLOAT;
  //        case sizeof(float) * 3:
  //          return DXGI_FORMAT_R32G32B32_FLOAT;
  //        case sizeof(float) * 2:
  //          return DXGI_FORMAT_R32G32_FLOAT;
  //        case sizeof(float) :
  //          return DXGI_FORMAT_R32_FLOAT;
  //        default:
  //          break;
  //      }
  //    }
  //    case DataType::Unsigned:
  //    {
  //      switch (param.size)
  //      {
  //        case sizeof(unsigned) * 4:
  //          return DXGI_FORMAT_R32G32B32A32_UINT;
  //        case sizeof(unsigned) * 3:
  //          return DXGI_FORMAT_R32G32B32_UINT;
  //        case sizeof(unsigned) * 2:
  //          return DXGI_FORMAT_R32G32_UINT;
  //        case sizeof(unsigned) :
  //          return DXGI_FORMAT_R32_UINT;
  //        default:
  //          break;
  //      }
  //    }
  //    case DataType::Typeless:
  //    {
  //      switch (param.size)
  //      {
  //        case sizeof(unsigned) * 4:
  //          return DXGI_FORMAT_R32G32B32A32_TYPELESS;
  //        case sizeof(unsigned) * 3:
  //          return DXGI_FORMAT_R32G32B32_TYPELESS;
  //        case sizeof(unsigned) * 2:
  //          return DXGI_FORMAT_R32G32_TYPELESS;
  //        case sizeof(unsigned) :
  //          return DXGI_FORMAT_R32_TYPELESS;
  //        default:
  //          break;
  //      }
  //    }
  //    default:
  //      break;
  //  }
  //  return DXGI_FORMAT_UNKNOWN;
  //}

  bool DxShader::InitLayout(ID3D10Blob* vertexShaderBuffer)
  {

    DirectX* dx = reinterpret_cast<DirectX*>(Graphics::graphicsAPI);
    SwapChain* swapChain = dx->GetSwapChain();
    ID3D11Device* device = swapChain->device->D3DDevice;


    //for now. later we might have to change this.
    if(layout_)
    {
      layout_->Release();
      layout_ = nullptr;
    }


    ID3D11ShaderReflection* vertShaderReflection = nullptr;
    DXError(D3DReflect(vertexShaderBuffer->GetBufferPointer(),
                       vertexShaderBuffer->GetBufferSize(),
                       IID_ID3D11ShaderReflection, 
                       (void**) &vertShaderReflection));
    
    D3D11_SHADER_DESC shaderDesc;
    vertShaderReflection->GetDesc(&shaderDesc);
    
    // Read input layout description from shader info
    std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
    for(unsigned i = 0; i < shaderDesc.InputParameters; i++)
    {
      ParamTypeInfo newParam;
      D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
      vertShaderReflection->GetInputParameterDesc(i, &paramDesc);
      
      
      // fill out input element desc
      D3D11_INPUT_ELEMENT_DESC elementDesc;
      elementDesc.SemanticName = paramDesc.SemanticName;
      elementDesc.SemanticIndex = paramDesc.SemanticIndex;
      elementDesc.InputSlot = 0;
      elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
      elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
      elementDesc.InstanceDataStepRate = 0;
      if(paramDesc.Mask == 1)
      {
        if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
      }
      else if(paramDesc.Mask <= 3)
      {
        if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
      }
      else if(paramDesc.Mask <= 7)
      {
        if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
      }
      else if(paramDesc.Mask <= 15)
      {
        if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
        else if(paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
      }
      inputLayoutDesc.push_back(elementDesc);
    }
    
    
    
    
    
    
    
    for(size_t i = 0; i < shaderDesc.ConstantBuffers; i++)
    {
      ID3D11ShaderReflectionConstantBuffer* pConstantReflection = vertShaderReflection->GetConstantBufferByIndex(i);
      D3D11_SHADER_BUFFER_DESC desc;
      DXError(pConstantReflection->GetDesc(&desc));
      DxBuffer* newBuf = new DxBuffer(desc.Name,
                                      0,
                                      0,
                                      nullptr,
                                      desc.Size,
                                      BufferType::Constant,
                                      AccessType::CpuWrite,
                                      UsageType::Dynamic);
      
      for(size_t varInd = 0; varInd < desc.Variables; ++varInd)
      {
        ID3D11ShaderReflectionVariable* curVar = pConstantReflection->GetVariableByIndex(varInd);
        D3D11_SHADER_VARIABLE_DESC varDesc;
        DXError(curVar->GetDesc(&varDesc));
        newBuf->AddParameter({varDesc.Name, varDesc.Size, varDesc.StartOffset});
        
      }
      newBuf->Initialize();
      AddConstantBuffer(newBuf);
      //m_cBuffer[i] = new d3d::ConstantBuffer(*m_pDevice, desc.Size);
    }
    int bufSize = vertexShaderBuffer->GetBufferSize();
    DXError(device->CreateInputLayout(&inputLayoutDesc[0],
                                      inputLayoutDesc.size(),
                                      vertexShaderBuffer->GetBufferPointer(),
                                      vertexShaderBuffer->GetBufferSize(),
                                      &layout_));

    //vertShaderReflection->Release();
    return true;
  }

  void DxShader::Render(int indexCount)
  {
    if (!pixel_shader_ || !vertex_shader_)
    {
      return;
    }
    RenderShader(indexCount);
  }

  void DxShader::SetShaderDir(const std::string& dir)
  {
    ConsolePrint("Why do you call");
  }


}