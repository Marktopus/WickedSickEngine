#include "GraphicsPrecompiled.h"
#include "DxBuffer.h"

#include "D3D/DXIncludes.h"

#include "API/DirectX.h"
#include "D3D/SwapChain.h"
#include "D3D/Device.h"

#include "System/Graphics.h"

#include "General/GraphicsUtility.h"



namespace WickedSick
{
  DxBuffer::DxBuffer( size_t stride,
                      size_t offset,
                      void* data,
                      size_t size,
                      Type  type) 
                      : Buffer( stride, 
                                offset, 
                                data, 
                                size, 
                                type)
  {

  }

  DxBuffer::~DxBuffer()
  {

  }
  
  void DxBuffer::Initialize()
  {
    DirectX* dx = (DirectX*)Graphics::graphicsAPI;
    ID3D11Device* device = dx->GetSwapChain()->device->D3DDevice;
    D3D11_BUFFER_DESC bufferDesc;
    D3D11_SUBRESOURCE_DATA* buffData = nullptr;

    
    bufferDesc.ByteWidth = size_;

    switch (type_)
    {
    case Buffer::Vertex:
      bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      bufferDesc.Usage = D3D11_USAGE_DEFAULT;
      bufferDesc.CPUAccessFlags = 0;
      buffData = (D3D11_SUBRESOURCE_DATA*)alloca(sizeof(D3D11_SUBRESOURCE_DATA));
      buffData->pSysMem = data_;
      buffData->SysMemPitch = 0;
      buffData->SysMemSlicePitch = 0;
      break;
    case Buffer::Index:
      bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
      bufferDesc.Usage = D3D11_USAGE_DEFAULT;
      bufferDesc.CPUAccessFlags = 0;
      buffData = (D3D11_SUBRESOURCE_DATA*)alloca(sizeof(D3D11_SUBRESOURCE_DATA));
      buffData->pSysMem = data_;
      buffData->SysMemPitch = 0;
      buffData->SysMemSlicePitch = 0;
      break;
    case Buffer::Constant:
      bufferDesc.ByteWidth = size_ + (16 - (size_ % 16));
      bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
      bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
      bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
      bufferDesc.MiscFlags = 0;
      bufferDesc.StructureByteStride = 0;
      break;
    default:
      break;
    }

    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;



    DXError(device->CreateBuffer(&bufferDesc, 
                                 buffData, 
                                 &buffer_));
  }

  void* DxBuffer::BufferPointer()
  {
    return buffer_;
  }

}
