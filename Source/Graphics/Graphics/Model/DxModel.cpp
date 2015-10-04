#include "GraphicsPrecompiled.h"
#include "DxModel.h"
#include "Buffer/DxBuffer.h"

#include "API/DirectX.h"
#include "D3D/SwapChain.h"
#include "D3D/Device.h"
#include "System/Graphics.h"


#define _NO_DEBUG_HEAP

namespace WickedSick
{

  DxModel::DxModel()
  {

  }
  
  DxModel::~DxModel()
  {

  }
  
  void DxModel::Initialize()
  {

    vertex_buffer_ = new DxBuffer(sizeof(Vertex),
                                  0,
                                  &vertex_list_[0],
                                  sizeof(Vertex) * GetNumVerts(),
                                  WickedSick::Buffer::Vertex);
    index_buffer_ = new DxBuffer( sizeof(int),
                                  0,
                                  &face_list_[0],
                                  sizeof(int) * GetNumIndices(),
                                  WickedSick::Buffer::Index);

    vertex_buffer_->Initialize();
    index_buffer_->Initialize();
  }
  
  void DxModel::Render()
  {

    DirectX* dx = (DirectX*)Graphics::graphicsAPI;
    ID3D11DeviceContext* context = dx->GetSwapChain()->device->D3DContext;

    DxBuffer* vert = (DxBuffer*)vertex_buffer_;
    DxBuffer* index = (DxBuffer*)index_buffer_;

    ID3D11Buffer* vertBuf = (ID3D11Buffer*)vert->BufferPointer();
    ID3D11Buffer* indBuf = (ID3D11Buffer*)index->BufferPointer();

    
    // Set the vertex buffer to active in the input assembler so it can be rendered.
    context->IASetVertexBuffers(0, 
                                1, 
                                &vertBuf, 
                                &vert->stride_, 
                                &vert->offset_);

    // Set the index buffer to active in the input assembler so it can be rendered.
    context->IASetIndexBuffer(indBuf, 
                              DXGI_FORMAT_R32_UINT, 
                              0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  }
}
