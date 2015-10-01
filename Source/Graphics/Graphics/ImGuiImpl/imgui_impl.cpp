// ImGui Win32 + DirectX11 binding
// https://github.com/ocornut/imgui
#include "GraphicsPrecompiled.h"
#include "Core/CoreInterface.h"
#include "GraphicsInterface.h"
#include "General/GraphicsUtility.h"
#include "Imgui/include/imgui.h"
#include "imgui_impl.h"
#include "Buffer/DxBuffer.h"
#include "API/DirectX.h"
#include "D3D/Device.h"
#include "D3D/SwapChain.h"



// This is the main rendering function that you have to implement and provide to ImGui (via setting up 'RenderDrawListsFn' in the ImGuiIO structure)
// If text or lines are blurry when integrating ImGui in your engine:
// - in your Render function, try translating your projection matrix by (0.5f,0.5f) or (0.375f,0.375f)

struct VERTEX_CONSTANT_BUFFER
{
  float        mvp[4][4];
};

#if 0
static void DxImguiRender(ImDrawData* draw_data)
{
  using namespace WickedSick;
  Graphics* gSys = (Graphics*)Engine::GetCore()->GetSystem(ST_Graphics);
  static Renderable* imGuiRenderable = gSys->GetRenderable("Imgui");
  DirectX* dx = (DirectX*)Graphics::graphicsAPI;

  DxBuffer* vertBuf = (DxBuffer*) imGuiRenderable->vertBuf;
  DxBuffer* indBuf = (DxBuffer*) imGuiRenderable->indexBuf;

  Shader* imguiShader = gSys->GetShader("Imgui");
  

  // Create and grow vertex/index buffers if needed
  if (!imGuiRenderable->vertBuf || imGuiRenderable->vertBuf->GetSize() < (draw_data->TotalVtxCount + 5000))
  {
    if (imGuiRenderable->vertBuf)
    {
      imGuiRenderable->vertBuf->ClearBuffer();
      new (imGuiRenderable->vertBuf) DxBuffer("Vertex",
                                              0,
                                              0,
                                              nullptr,
                                              sizeof(ImDrawVert) * (draw_data->TotalVtxCount + 5000),
                                              BufferType::Vertex,
                                              AccessType::CpuWrite,
                                              UsageType::Dynamic);
    }
    else
    {
      imGuiRenderable->vertBuf = new DxBuffer("Vertex", 
                                              0,
                                              0,
                                              nullptr,
                                              sizeof(ImDrawVert) * (draw_data->TotalVtxCount + 5000),
                                              BufferType::Vertex,
                                              AccessType::CpuWrite,
                                              UsageType::Dynamic);
    }

  }
  if (!imGuiRenderable->indexBuf || imGuiRenderable->indexBuf->GetSize() < (draw_data->TotalIdxCount + 10000))
  {

    if (imGuiRenderable->indexBuf)
    {
      imGuiRenderable->indexBuf->ClearBuffer();
      new (imGuiRenderable->indexBuf) DxBuffer("Pixel",
                                               0,
                                               0,
                                               nullptr,
                                               sizeof(ImDrawIdx) * (draw_data->TotalIdxCount + 10000),
                                               BufferType::Index,
                                               AccessType::CpuWrite,
                                               UsageType::Dynamic);
    }
    else
    {
      imGuiRenderable->indexBuf = new DxBuffer("Pixel",
                                               0,
                                               0,
                                               nullptr,
                                               sizeof(ImDrawVert) * (draw_data->TotalIdxCount + 10000),
                                               BufferType::Index,
                                               AccessType::CpuWrite,
                                               UsageType::Dynamic);
    }

  }

  Device* dev = dx->GetSwapChain()->device;
  // Copy and convert all vertices into a single contiguous buffer




  ImDrawVert* vtx_dst = (ImDrawVert*)vertBuf->BufferPointer();
  ImDrawIdx* idx_dst = (ImDrawIdx*)indBuf->BufferPointer();
  for (int n = 0; n < draw_data->CmdListsCount; n++)
  {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];
    memcpy(vtx_dst, &cmd_list->VtxBuffer[0], cmd_list->VtxBuffer.size() * sizeof(ImDrawVert));
    memcpy(idx_dst, &cmd_list->IdxBuffer[0], cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx));
    vtx_dst += cmd_list->VtxBuffer.size();
    idx_dst += cmd_list->IdxBuffer.size();
  }

  DxBuffer* imguiCbuffer = (DxBuffer*)imguiShader->GetConstantBuffer("vertexBuffer");
  const float L = 0.0f;
  const float R = ImGui::GetIO().DisplaySize.x;
  const float B = ImGui::GetIO().DisplaySize.y;
  const float T = 0.0f;
  Matrix4 projection = Matrix4(2.0f / (R - L), 0.0f, 0.0f, 0.0f,
                               0.0f, 2.0f / (T - B), 0.0f, 0.0f,
                               0.0f, 0.0f, 0.5f, 0.0f,
                               (R + L) / (L - R), (T + B) / (B - T), 0.5f, 1.0f);
  imguiCbuffer->SetParameter("ProjectionMatrix", &projection);

  

  // Setup viewport(should be done already...)
  //{
  //  D3D11_VIEWPORT vp;
  //  memset(&vp, 0, sizeof(D3D11_VIEWPORT));
  //  vp.Width = ImGui::GetIO().DisplaySize.x;
  //  vp.Height = ImGui::GetIO().DisplaySize.y;
  //  vp.MinDepth = 0.0f;
  //  vp.MaxDepth = 1.0f;
  //  vp.TopLeftX = 0;
  //  vp.TopLeftY = 0;
  //  g_pd3dDeviceContext->RSSetViewports(1, &vp);
  //}

  // Bind shader and vertex buffers
  unsigned int stride = sizeof(ImDrawVert);
  unsigned int offset = 0;
  g_pd3dDeviceContext->IASetInputLayout(g_pInputLayout);
  g_pd3dDeviceContext->IASetVertexBuffers(0, 1, &g_pVB, &stride, &offset);
  g_pd3dDeviceContext->IASetIndexBuffer(g_pIB, DXGI_FORMAT_R16_UINT, 0);
  g_pd3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  g_pd3dDeviceContext->VSSetShader(g_pVertexShader, NULL, 0);
  g_pd3dDeviceContext->VSSetConstantBuffers(0, 1, &g_pVertexConstantBuffer);
  g_pd3dDeviceContext->PSSetShader(g_pPixelShader, NULL, 0);
  g_pd3dDeviceContext->PSSetSamplers(0, 1, &g_pFontSampler);

  // Setup render state
  const float blendFactor[4] = { 0.f, 0.f, 0.f, 0.f };
  g_pd3dDeviceContext->OMSetBlendState(g_pBlendState, blendFactor, 0xffffffff);
  g_pd3dDeviceContext->RSSetState(g_pRasterizerState);

  // Render command lists
  int vtx_offset = 0;
  int idx_offset = 0;
  for (int n = 0; n < draw_data->CmdListsCount; n++)
  {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];
    for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
    {
      const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
      if (pcmd->UserCallback)
      {
        pcmd->UserCallback(cmd_list, pcmd);
      }
      else
      {
        const D3D11_RECT r = {(LONG) pcmd->ClipRect.x, (LONG) pcmd->ClipRect.y, (LONG) pcmd->ClipRect.z, (LONG) pcmd->ClipRect.w};
        g_pd3dDeviceContext->PSSetShaderResources(0, 1, (ID3D11ShaderResourceView**) &pcmd->TextureId);
        g_pd3dDeviceContext->RSSetScissorRects(1, &r);
        g_pd3dDeviceContext->DrawIndexed(pcmd->ElemCount, idx_offset, vtx_offset);
      }
      idx_offset += pcmd->ElemCount;
    }
    vtx_offset += cmd_list->VtxBuffer.size();
  }

  // Restore modified state
  g_pd3dDeviceContext->IASetInputLayout(NULL);
  g_pd3dDeviceContext->PSSetShader(NULL, NULL, 0);
  g_pd3dDeviceContext->VSSetShader(NULL, NULL, 0);
}
#endif

void ImGui_ImplDX11_RenderDrawLists(ImDrawData* draw_data)
{

  using namespace WickedSick;
  Graphics* gSys = (Graphics*) Engine::GetCore()->GetSystem(ST_Graphics);

  static ID3D11Buffer*  vertexCBuffer = nullptr;
  static ID3D11Buffer*  vb = nullptr;
  static ID3D11Buffer*  ib = nullptr;
  static ID3D11VertexShader*      vertShader = nullptr;
  static ID3D11PixelShader*       pixelShader = nullptr;
  static ID3D11SamplerState*      fontSampler = nullptr;
  static ID3D11ShaderResourceView* fontTexView = nullptr;
  static ID3D11RasterizerState*   rasterizerState = nullptr;
  static ID3D11BlendState*        blendState = nullptr;
  static ID3D11InputLayout*       inputLayout = nullptr;
  static size_t vbSize = 0;
  static size_t ibSize = 0;
  DirectX* dx = (DirectX*) Graphics::graphicsAPI;

  ID3D11Device* device = dx->GetSwapChain()->device->D3DDevice;
  ID3D11DeviceContext* context = dx->GetSwapChain()->device->D3DContext;

  // Create and grow vertex/index buffers if needed
  if(!vb || vbSize < (draw_data->TotalVtxCount + 5000))
  {
    if(vb)
    {
      vb->Release(); vb = NULL;
    }
    vbSize = draw_data->TotalVtxCount + 5000;
    D3D11_BUFFER_DESC desc;
    memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.ByteWidth = vbSize * sizeof(ImDrawVert);
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;
    if(device->CreateBuffer(&desc, NULL, &vb) < 0)
      return;
  }
  if(!ib || ibSize < (draw_data->TotalIdxCount + 10000))
  {
    if(ib)
    {
      ib->Release(); ib = NULL;
    }
    ibSize = draw_data->TotalIdxCount + 10000;
    D3D11_BUFFER_DESC bufferDesc;
    memset(&bufferDesc, 0, sizeof(D3D11_BUFFER_DESC));
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.ByteWidth = ibSize * sizeof(ImDrawIdx);
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    if(device->CreateBuffer(&bufferDesc, NULL, &ib) < 0)
      return;
  }

  // Copy and convert all vertices into a single contiguous buffer
  D3D11_MAPPED_SUBRESOURCE vtx_resource, idx_resource;
  if(context->Map(vb, 0, D3D11_MAP_WRITE_DISCARD, 0, &vtx_resource) != S_OK)
    return;
  if(context->Map(ib, 0, D3D11_MAP_WRITE_DISCARD, 0, &idx_resource) != S_OK)
    return;
  ImDrawVert* vtx_dst = (ImDrawVert*) vtx_resource.pData;
  ImDrawIdx* idx_dst = (ImDrawIdx*) idx_resource.pData;
  for(int n = 0; n < draw_data->CmdListsCount; n++)
  {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];
    memcpy(vtx_dst, &cmd_list->VtxBuffer[0], cmd_list->VtxBuffer.size() * sizeof(ImDrawVert));
    memcpy(idx_dst, &cmd_list->IdxBuffer[0], cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx));
    vtx_dst += cmd_list->VtxBuffer.size();
    idx_dst += cmd_list->IdxBuffer.size();
  }
  context->Unmap(vb, 0);
  context->Unmap(ib, 0);

  // Setup orthographic projection matrix into our constant buffer
  {
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    if(context->Map(vertexCBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource) != S_OK)
      return;

    VERTEX_CONSTANT_BUFFER* pConstantBuffer = (VERTEX_CONSTANT_BUFFER*) mappedResource.pData;
    const float L = 0.0f;
    const float R = ImGui::GetIO().DisplaySize.x;
    const float B = ImGui::GetIO().DisplaySize.y;
    const float T = 0.0f;
    const float mvp[4][4] =
    {
      {2.0f / (R - L),   0.0f,           0.0f,       0.0f},
      {0.0f,         2.0f / (T - B),     0.0f,       0.0f,},
      {0.0f,         0.0f,           0.5f,       0.0f},
      {(R + L) / (L - R),  (T + B) / (B - T),    0.5f,       1.0f},
    };
    memcpy(&pConstantBuffer->mvp, mvp, sizeof(mvp));
    context->Unmap(vertexCBuffer, 0);
  }

  // Setup viewport
  {
    D3D11_VIEWPORT vp;
    memset(&vp, 0, sizeof(D3D11_VIEWPORT));
    vp.Width = ImGui::GetIO().DisplaySize.x;
    vp.Height = ImGui::GetIO().DisplaySize.y;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    context->RSSetViewports(1, &vp);
  }

  // Bind shader and vertex buffers
  unsigned int stride = sizeof(ImDrawVert);
  unsigned int offset = 0;
  context->IASetInputLayout(inputLayout);
  context->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
  context->IASetIndexBuffer(ib, DXGI_FORMAT_R16_UINT, 0);
  context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  context->VSSetShader(vertShader, NULL, 0);
  context->VSSetConstantBuffers(0, 1, &vertexCBuffer);
  context->PSSetShader(pixelShader, NULL, 0);
  context->PSSetSamplers(0, 1, &fontSampler);

  // Setup render state
  const float blendFactor[4] = {0.f, 0.f, 0.f, 0.f};
  context->OMSetBlendState(blendState, blendFactor, 0xffffffff);
  context->RSSetState(rasterizerState);

  // Render command lists
  int vtx_offset = 0;
  int idx_offset = 0;
  for(int n = 0; n < draw_data->CmdListsCount; n++)
  {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];
    for(int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
    {
      const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
      if(pcmd->UserCallback)
      {
        pcmd->UserCallback(cmd_list, pcmd);
      }
      else
      {
        const D3D11_RECT r = {(LONG) pcmd->ClipRect.x, (LONG) pcmd->ClipRect.y, (LONG) pcmd->ClipRect.z, (LONG) pcmd->ClipRect.w};
        context->PSSetShaderResources(0, 1, (ID3D11ShaderResourceView**) &pcmd->TextureId);
        context->RSSetScissorRects(1, &r);
        context->DrawIndexed(pcmd->ElemCount, idx_offset, vtx_offset);
      }
      idx_offset += pcmd->ElemCount;
    }
    vtx_offset += cmd_list->VtxBuffer.size();
  }

  // Restore modified state
  context->IASetInputLayout(NULL);
  context->PSSetShader(NULL, NULL, 0);
  context->VSSetShader(NULL, NULL, 0);
}