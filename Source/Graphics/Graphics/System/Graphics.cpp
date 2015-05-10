#include "GraphicsPrecompiled.h"
#include "Graphics.h"

#include "../D3D/Device.h"
#include "../D3D/SwapChain.h"

#include "Core/CoreInterface.h"
#include "Window/WindowInterface.h"

#include "Graphics/DXIncludes.h"

#include "d3d11.h"

#include "Graphics/Camera/Camera.h"

#include "Graphics/Model/Model.h"
#include "Graphics/Shader/Shader.h"


#include <thread>
#include <mutex>

namespace WickedSick
{
  GRAPHICSDLL_API Graphics::Graphics() : System(System::Graphics)
  {
  }

  GRAPHICSDLL_API Graphics::~Graphics()
  {
    delete swap_chain_;

    //BAAAD
    back_buffer_->Release();
  }

  GRAPHICSDLL_API void Graphics::Initialize()
  {

    swap_chain_ = new SwapChain();
    camera_ = new Camera();
    model_ = new Model();//temp as fuck
    shader_ = new Shader(); //still temp
    
    WickedSick::Window* window = (WickedSick::Window*)core_->GetSystem(System::Window);
    while (!window->GetCore() || !window->GetWindowHandle())
    {
      Sleep(1);
    }

    core_->GetSystem<WickedSick::Window>(System::Window);
    std::lock_guard<std::mutex> lk(window->GetWindowHandleMutex());
    swap_chain_->Initialize(window->GetWindowHandle(), window->GetWindowSize());


    ID3D11Texture2D* backBufferPtr;
    // Get the pointer to the back buffer.
	  swap_chain_->D3DSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);

	  // Create the render target view with the back buffer pointer.
	  swap_chain_->device->D3DDevice->CreateRenderTargetView(backBufferPtr, NULL, &render_target_view_);
	  
	  // Release pointer to the back buffer as we no longer need it.
	  backBufferPtr->Release();
	  backBufferPtr = 0;

    
    D3D11_TEXTURE2D_DESC depthBufferDesc;
    ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
    depthBufferDesc.Width = window->GetWindowSize().x;
	  depthBufferDesc.Height = window->GetWindowSize().y;
	  depthBufferDesc.MipLevels = 1;
	  depthBufferDesc.ArraySize = 1;
	  depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	  depthBufferDesc.SampleDesc.Count = 1;
	  depthBufferDesc.SampleDesc.Quality = 0;
	  depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	  depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	  depthBufferDesc.CPUAccessFlags = 0;
	  depthBufferDesc.MiscFlags = 0;

    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

    // Set up the description of the stencil state.
	  depthStencilDesc.DepthEnable = true;
	  depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	  depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	  depthStencilDesc.StencilEnable = true;
	  depthStencilDesc.StencilReadMask = 0xFF;
	  depthStencilDesc.StencilWriteMask = 0xFF;

	  // Stencil operations if pixel is front-facing.
	  depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	  depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	  depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	  depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	  // Stencil operations if pixel is back-facing.
	  depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	  depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	  depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	  depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Create the depth stencil state.
    swap_chain_->device->D3DDevice->CreateDepthStencilState(&depthStencilDesc, &depth_stencil_state_);
    swap_chain_->device->D3DContext->OMSetDepthStencilState(depth_stencil_state_, 1);
  
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	  // Set up the depth stencil view description.
	  depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	  depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	  depthStencilViewDesc.Texture2D.MipSlice = 0;

	  // Create the depth stencil view.
    swap_chain_->device->D3DDevice->CreateTexture2D(&depthBufferDesc, NULL, &depth_stencil_buffer_);

	  swap_chain_->device->D3DDevice->CreateDepthStencilView(depth_stencil_buffer_, &depthStencilViewDesc, &depth_stencil_view_);
    swap_chain_->device->D3DContext->OMSetRenderTargets(1, &render_target_view_, depth_stencil_view_);


    D3D11_RASTERIZER_DESC rasterDesc;
    rasterDesc.AntialiasedLineEnable = false;
	  rasterDesc.CullMode = D3D11_CULL_BACK;
	  rasterDesc.DepthBias = 0;
	  rasterDesc.DepthBiasClamp = 0.0f;
	  rasterDesc.DepthClipEnable = true;
	  rasterDesc.FillMode = D3D11_FILL_SOLID;
	  rasterDesc.FrontCounterClockwise = false;
	  rasterDesc.MultisampleEnable = false;
	  rasterDesc.ScissorEnable = false;
	  rasterDesc.SlopeScaledDepthBias = 0.0f;

	  // Create the rasterizer state from the description we just filled out.
	  swap_chain_->device->D3DDevice->CreateRasterizerState(&rasterDesc, &rasterizer_state_);
	  
    swap_chain_->device->D3DContext->RSSetState(rasterizer_state_);

    D3D11_VIEWPORT viewport;
    viewport.Width = (float)window->GetWindowSize().x;
	  viewport.Height = (float)window->GetWindowSize().y;
	  viewport.MinDepth = 0.0f;
	  viewport.MaxDepth = 1.0f;
	  viewport.TopLeftX = 0.0f;
	  viewport.TopLeftY = 0.0f;

	  // Create the viewport.
	  swap_chain_->device->D3DContext->RSSetViewports(1, &viewport);

    // Setup the projection matrix.
	  float fieldOfView = (float)PI / 4.0f;//90 degrees
	  float screenAspect = (float)window->GetWindowSize().x / (float)window->GetWindowSize().y;

	  // Create the projection matrix for 3D rendering.
    projection_matrix_.DoPerspective(fieldOfView, 0.1f, 1000.0f, screenAspect);

    world_matrix_.Identity();

    orthographic_matrix_.DoOrthographic(window->GetWindowSize().x, window->GetWindowSize().y, 0.1f, 1000.0f);



    model_->Initialize(swap_chain_->device->D3DDevice);
    shader_->Initialize(swap_chain_->device->D3DDevice, window->GetWindowHandle());
    camera_->SetPosition(0.0f, 0.0f, -0.5f);

  }

  GRAPHICSDLL_API bool Graphics::Load()
  {
    return true;
  }

  GRAPHICSDLL_API bool Graphics::Reload()
  {
    return true;
  }

  GRAPHICSDLL_API void Graphics::Update(double dt)
  {
    RenderFrame();
  }

  GRAPHICSDLL_API void Graphics::ReceiveMessage()
  {

  }
  
  void Graphics::RenderFrame()
  {
    BeginScene();

    camera_->Render();
    
    model_->Render(swap_chain_->device->D3DContext);
    shader_->Render(swap_chain_->device->D3DContext, model_->GetIndexCount(), world_matrix_, camera_->GetViewMatrix(), projection_matrix_);

    EndScene();
  }

  void Graphics::BeginScene()
  {
    float color[4];


	  // Setup the color to clear the buffer to.
	  color[0] = 0.1f;
	  color[1] = 0.1f;
	  color[2] = 0.1f;
	  color[3] = 1.0f;

	  // Clear the back buffer.
	  swap_chain_->device->D3DContext->ClearRenderTargetView(render_target_view_, color);
    
	  // Clear the depth buffer.
	  swap_chain_->device->D3DContext->ClearDepthStencilView(depth_stencil_view_, D3D11_CLEAR_DEPTH, 1.0f, 0);

	  return;
  }

  void Graphics::EndScene()
  {
    // Present the back buffer to the screen since rendering is complete.
	  if(false)//vsync
	  {
		  // Lock to screen refresh rate.
		  swap_chain_->D3DSwapChain->Present(1, 0);
	  }
	  else
	  {
		  // Present as fast as possible.
		  swap_chain_->D3DSwapChain->Present(0, 0);
	  }
  }


}
