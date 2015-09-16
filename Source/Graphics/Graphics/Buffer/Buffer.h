#pragma once

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

  class Buffer
  {
  public:

    enum Type
    {
      Vertex,
      Index,
      Constant,
      Count
    };


    Buffer( size_t stride,
            size_t offset,
            void* data,
            size_t size,
            Type  type);
    Buffer(const Buffer& buffer);
    virtual ~Buffer() = 0;

    virtual void* BufferPointer() = 0;
    virtual void Initialize() = 0;
    void Set( size_t stride,
              size_t offset,
              void* data,
              size_t size,
              Type  type);

  protected:

    

    size_t  stride_;
    size_t  offset_;

    void*   data_;
    size_t  size_;
    Type    type_;

  };
}