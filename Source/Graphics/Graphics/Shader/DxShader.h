#pragma once

#include "Shader/Shader.h"

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11ComputeShader;
struct ID3D11GeometryShader;
struct ID3D11InputLayout;
struct ID3D10Blob;

namespace WickedSick
{
  struct LightBuffer
  {
    Matrix4 modelToWorld;
    Matrix4 worldToClip;
    Vector3 lightDir;
    Vector3 cameraVec;
  };

  class DxShader : public Shader
  {
  public:
    DxShader(const std::string& name,
             ShaderCallback callback);
    ~DxShader();

    void Initialize();

    bool Compile(bool forceCompile = false);
    void ReflectBuffers();

    bool InitLayout(ID3D10Blob* vertexShaderBuffer);


    void Render(int indexCount);

    void SetShaderDir(const std::string& dir);
    
    void RenderShader(int indexCount);

    void SetParameters(const std::vector<ParamPasser>& params);


  private:



    ID3D11VertexShader*   vertex_shader_;
    ID3D11PixelShader*    pixel_shader_;
    ID3D11ComputeShader*  compute_shader_;
    ID3D11GeometryShader* geometry_shader_;
    ID3D11InputLayout*    layout_;

  };
}
