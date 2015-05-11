#pragma once

#include "GraphicsDLL.h"
#include "DXIncludes.h"
#include "Core/CoreInterface.h"

#include "Math/MathInterface.h"

struct ID3D11RenderTargetView;
namespace WickedSick
{
  class Shader;
  class Model;
  class Camera;
  struct Device;
  struct SwapChain;
  

  class Graphics : public System
  {
  public:
    GRAPHICSDLL_API Graphics();
    GRAPHICSDLL_API ~Graphics();
    GRAPHICSDLL_API void Initialize();
    GRAPHICSDLL_API bool Load();
    GRAPHICSDLL_API bool Reload();
    GRAPHICSDLL_API void Update(double dt);
    GRAPHICSDLL_API void ReceiveMessage(Message * msg);

    void BeginScene();
    void EndScene();
    //v bad.0
    void RenderFrame();

  private:
    SwapChain* swap_chain_;

    ID3D11RenderTargetView* back_buffer_;
    ID3D11DepthStencilState* depth_stencil_state_;
    ID3D11Texture2D* depth_stencil_buffer_;
    ID3D11DepthStencilView* depth_stencil_view_;
    ID3D11RenderTargetView* render_target_view_;
    ID3D11RasterizerState* rasterizer_state_;

    Camera* camera_;
    Model* model_;//temp as fuck
    Shader* shader_; //still temp

    Matrix4 projection_matrix_;
	  Matrix4 world_matrix_;
	  Matrix4 orthographic_matrix_;

  };
}
