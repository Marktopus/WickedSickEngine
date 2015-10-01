#pragma once
#include "Buffer.h"

struct ID3D11Device;
struct ID3D11Buffer;
namespace WickedSick
{
  
  class DxBuffer : public Buffer
  {
  public:
    DxBuffer(const std::string& name,
             size_t stride,
             size_t offset,
             void* init,
             size_t size,
             BufferType::Enum  type,
             AccessType::Enum accessType,
             UsageType::Enum usageType);
    DxBuffer(const DxBuffer& buffer);
    ~DxBuffer();

    void Initialize() override;
    void ClearBuffer() override;
    void* BufferPointer() override;
  private:

    friend class DirectX;
    friend class DxModel;

    ID3D11Buffer* buffer_;
  };
}
