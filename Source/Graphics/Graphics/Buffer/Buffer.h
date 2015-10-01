#pragma once
#include "Utility/UtilityInterface.h"
#include "Shader/ParamTypeInfo.h"

namespace WickedSick
{
  enum DrawMethod
  {
    PointList,
    LineList,
    TriangleList,
    TriangleStrip,
    
    Count
  };

  namespace AccessType
  {
    enum Enum
    {
      None,
      CpuWrite,
      CpuRead,
      CpuBoth
    };
  }

  namespace UsageType
  {
    enum Enum
    {
      Default,//read/write via gpu
      Dynamic,//read access via gpu, write via cpu
      Static,//read-only, no cpu access
      Staging//can copy from gpu to cpu
    };
  }

  namespace BufferType
  {
    enum Enum
    {
      Vertex,
      Index,
      Constant,
      Count
    };
  }
  struct ParamTypeInfo;
  class Buffer
  {
  public:

    Buffer(const std::string& name,
           size_t stride,
           size_t offset,
           void* init,
           size_t size,
           BufferType::Enum  type,
           AccessType::Enum accessType,
           UsageType::Enum usageType);
    Buffer(const Buffer& buffer);
    virtual ~Buffer();

    virtual void* BufferPointer() = 0;
    virtual void* GetData() final;
    virtual void Initialize() = 0;
    virtual void ClearBuffer() = 0;

    size_t GetSize();
    virtual std::string GetName() final;
    void AddParameter(ParamTypeInfo&& param);
    void AddParameter(const ParamTypeInfo& param);
    void SetParameter(const std::string& name, void* data);
    virtual HashMap<std::string, ParamTypeInfo>& GetParameters();

  protected:

    std::string name_;

    size_t  stride_;
    size_t  offset_;

    void*   data_;
    size_t  size_;
    size_t  buf_num_;
    BufferType::Enum type_;
    AccessType::Enum access_type_;
    UsageType::Enum  usage_type_;

    HashMap<std::string, ParamTypeInfo> parameters_;
  };
}