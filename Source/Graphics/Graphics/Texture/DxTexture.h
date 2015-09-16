#pragma once

#include "Texture.h"

namespace WickedSick
{
  struct ID3D11Texture2D;

  class DxTexture : public Texture
  {
  public:
    DxTexture();
    ~DxTexture();
    void Initialize();
    void* GetTexturePointer();
  private:

    ID3D11Texture2D* texture_;

  };
}
