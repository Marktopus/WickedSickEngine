#pragma once

namespace WickedSick
{
  class Texture
  {
  public:
    Texture();
    virtual ~Texture();
    virtual void* GetTexturePointer() = 0;
  private:
  };
}