#pragma once
#include "Buffer.h"

struct ID3D11Device;
struct ID3D11Buffer;
namespace WickedSick
{
  
  class DxBuffer : public Buffer
  {
  public:
    DxBuffer( size_t stride,
              size_t offset,
              void* data,
              size_t size,
              Type  type);
    DxBuffer(const DxBuffer& buffer);
    ~DxBuffer();

    void Initialize();

    void* BufferPointer();
  private:

    friend class DirectX;
    friend class DxModel;

    ID3D11Buffer* buffer_;
  };
}
