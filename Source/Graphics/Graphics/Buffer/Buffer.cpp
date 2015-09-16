#include "GraphicsPrecompiled.h"
#include "Buffer.h"

namespace WickedSick
{
  Buffer::Buffer( size_t stride,
                  size_t offset,
                  void* data,
                  size_t size,
                  Type  type)
                  : stride_(stride),
                    offset_(offset),
                    data_(data),
                    size_(size),
                    type_(type)
  {

  }

  Buffer::Buffer( const Buffer& buffer)
                  : stride_(buffer.stride_),
                    offset_(buffer.offset_),
                    data_(buffer.data_),
                    size_(buffer.size_),
                    type_(buffer.type_)
  {

  }

  Buffer::~Buffer()
  {

  }

  void Buffer::Set( size_t stride,
                    size_t offset,
                    void* data,
                    size_t size,
                    Type  type)
  {
    stride_ = stride;
    offset_ = offset;
    data_ = data;
    size_ = size;
    type_ = type;
  }
}
