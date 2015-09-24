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

  DxShader::DxShader() : vertex_shader_(nullptr),
                         pixel_shader_(nullptr),
                         compute_shader_(nullptr),
                         geometry_shader_(nullptr),
                         layout_(nullptr)
  {

  }
  
  DxShader::~DxShader()
  {

  }

  void DxShader::Initialize()
  {
    matrix_buffer_ = new DxBuffer( 0, 
                                   0, 
                                   nullptr, 
                                   sizeof(LightBuffer),
                                   Buffer::Constant);
    matrix_buffer_->Initialize();

    if (!Compile(true))
    {
      ConsolePrint("One or more shaders failed to compile.\n");
    }

  }

  void DxShader::SetParameters( const Matrix4& world,
                                const Matrix4& clip, 
                                const Vector3& cameraPos)
  {
    DirectX* dx = reinterpret_cast<DirectX*>(Graphics::graphicsAPI);
    SwapChain* swapChain = dx->GetSwapChain();
    ID3D11DeviceContext* context = swapChain->device->D3DContext;

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    LightBuffer* dataPtr;
    ID3D11Buffer* buffer = (ID3D11Buffer*)matrix_buffer_->BufferPointer();

    unsigned int bufferNumber = 0;


    DXError(context->Map( buffer, 
                          0, 
                          D3D11_MAP_WRITE_DISCARD, 
                          0, 
                          &mappedResource));



    dataPtr = (LightBuffer*)mappedResource.pData;



    // Copy the matrices into the constant buffer.
    dataPtr->modelToWorld = world;//.GetTranspose();;
    dataPtr->worldToClip = clip;//.GetTranspose();
    dataPtr->lightDir = Vector3(1, 1, 1);
    dataPtr->cameraVec = cameraPos;

    // Unlock the constant buffer.
    context->Unmap(buffer, 0);

    context->VSSetConstantBuffers(bufferNumber, 1, &buffer);
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
                                  "ColorVertexShader", 
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
                                  "ColorPixelShader", 
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

  bool DxShader::InitLayout(ID3D10Blob* vertexShaderBuffer)
  {

    DirectX* dx = reinterpret_cast<DirectX*>(Graphics::graphicsAPI);
    SwapChain* swapChain = dx->GetSwapChain();
    ID3D11Device* device = swapChain->device->D3DDevice;

    D3D11_INPUT_ELEMENT_DESC polygonLayout[3];

    //for now. later we might have to change this.
    if (layout_)
    {
      layout_->Release();
    }
    polygonLayout[0].SemanticName = "POSITION";
    polygonLayout[0].SemanticIndex = 0;
    polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    polygonLayout[0].InputSlot = 0;
    polygonLayout[0].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    polygonLayout[0].InstanceDataStepRate = 0;

    polygonLayout[1].SemanticName = "COLOR";
    polygonLayout[1].SemanticIndex = 0;
    polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    polygonLayout[1].InputSlot = 0;
    polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    polygonLayout[1].InstanceDataStepRate = 0;

    polygonLayout[2].SemanticName = "NORMAL";
    polygonLayout[2].SemanticIndex = 0;
    polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    polygonLayout[2].InputSlot = 0;
    polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    polygonLayout[2].InstanceDataStepRate = 0;

    unsigned numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

    DXError(device->CreateInputLayout(polygonLayout,
                                      numElements,
                                      vertexShaderBuffer->GetBufferPointer(),
                                      vertexShaderBuffer->GetBufferSize(),
                                      &layout_));
    return true;
  }

  void DxShader::Render(int indexCount,
                        const Matrix4& world,
                        const Matrix4& clip,
                        const Vector3& cameraPos)
  {
    SetParameters(world, clip, cameraPos);
    RenderShader(indexCount);
  }

  void DxShader::SetShaderDir(const std::string& dir)
  {
    ConsolePrint("Why do you call");
  }

}