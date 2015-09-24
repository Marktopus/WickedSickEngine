#include "GraphicsPrecompiled.h"
#include "DirectX.h"

#include "Model/Model.h"

#include "General/GraphicsOptions.h"

#include "Window/WindowInterface.h"

#include "D3D/SwapChain.h"
#include "D3D/Device.h"
#include "Buffer/DxBuffer.h"

#include "General/GraphicsUtility.h"


namespace WickedSick
{
  DirectX::DirectX()  : swap_chain_(nullptr),
                        GraphicsAPI(DirectXAPI)
  {

  }

  DirectX::~DirectX()
  {

  }

  Model* DirectX::MakeModel()
  {
    return model_factory_.MakeBlank();
  }

  Shader* DirectX::MakeShader()
  {
    return shader_factory_.MakeBlank();
  }

  SwapChain* DirectX::GetSwapChain()
  {
    return swap_chain_;
  }

  void DirectX::Initialize( GraphicsOptions* options,
                            Window* window)
  {
    options_ = options;
    swap_chain_ = new SwapChain();
    swap_chain_->Initialize(window->GetWindowHandle(), window->GetWindowSize());

    /////////////////////////
    //all backbuffer stuff?
    ID3D11Texture2D* backBufferPtr;
    // Get the pointer to the back buffer.
    swap_chain_->D3DSwapChain->GetBuffer( 0, 
                                          __uuidof(ID3D11Texture2D), 
                                          (LPVOID*)&backBufferPtr);

    // Create the render target view with the back buffer pointer.
    DXError(swap_chain_->device->D3DDevice->CreateRenderTargetView( backBufferPtr, 
                                                                    nullptr, 
                                                                    &render_target_view_));
    
    // Release pointer to the back buffer as we no longer need it.
    backBufferPtr->Release();
    backBufferPtr = 0;
    // so make a generic backbuffer class probs?
    //////////////////////////

    //////////////////////////
    // depth buffer description
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
    //////////////////////////

    //////////////////////////
    //depth stencil description
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

    // Set up the description of the stencil state.
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

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
    DXError(swap_chain_->device->D3DDevice->CreateDepthStencilState(&depthStencilDesc, 
                                                                    &depth_stencil_state_));
    swap_chain_->device->D3DContext->OMSetDepthStencilState(depth_stencil_state_, 
                                                            1);
    //
    //////////////////////////


    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

    // Set up the depth stencil view description.
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    // Create the depth stencil view.
    DXError(swap_chain_->device->D3DDevice->CreateTexture2D(&depthBufferDesc, NULL, &depth_stencil_buffer_));

    DXError(swap_chain_->device->D3DDevice->CreateDepthStencilView( depth_stencil_buffer_, 
                                                                    &depthStencilViewDesc, 
                                                                    &depth_stencil_view_));
    swap_chain_->device->D3DContext->OMSetRenderTargets(1, 
                                                        &render_target_view_, 
                                                        depth_stencil_view_);

    D3D11_RASTERIZER_DESC rasterDesc;
    rasterDesc.AntialiasedLineEnable = false;
    rasterDesc.CullMode = D3D11_CULL_FRONT;
    rasterDesc.DepthBias = 0;
    rasterDesc.DepthBiasClamp = 0.0f;
    rasterDesc.DepthClipEnable = true;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.FrontCounterClockwise = true;
    rasterDesc.MultisampleEnable = false;
    rasterDesc.ScissorEnable = false;
    rasterDesc.SlopeScaledDepthBias = 0.0f;

    // Create the rasterizer state from the description we just filled out.
    DXError(swap_chain_->device->D3DDevice->CreateRasterizerState(&rasterDesc, 
                                                                  &rasterizer_state_));
    
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

  }

  void DirectX::CleanUp()
  {
    delete swap_chain_;

    //BAAAD
    back_buffer_->Release();
  }

  void DirectX::BeginScene()
  {
    clear_buffers();
  }

  void DirectX::RenderScene()
  {
    //do shader thing i guess
  }

  void DirectX::EndScene()
  {
    if(options_->VSync)//vsync
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
   
  void DirectX::clear_buffers()
  {
    // Clear the back buffer.
    swap_chain_->device->D3DContext->ClearRenderTargetView(render_target_view_, &(options_->ClearColor[0]));
    
    // Clear the depth buffer.
    swap_chain_->device->D3DContext->ClearDepthStencilView(depth_stencil_view_, D3D11_CLEAR_DEPTH, 1.0f, 0);
  }
}

