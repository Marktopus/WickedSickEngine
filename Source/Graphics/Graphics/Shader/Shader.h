#pragma once
#include "ParamTypeInfo.h"

#include "Math/MathInterface.h"
#include "Utility/UtilityInterface.h"

namespace WickedSick
{

  class Buffer;
  namespace ShaderType
  {
    enum Enum
    {
      Vertex,
      Pixel,
      Compute,
      Tesselation,
      Geometry,
      Count
    };
  }

  class Shader
  {
    public:
      Shader();
      ~Shader();

      virtual void Initialize() = 0;
      virtual bool Compile(bool forceCompile = false) = 0;
      virtual void ReflectBuffers() = 0;

      virtual void Render(int indexCount,
                          const std::vector<ParamPasser>& params) = 0;

      void SetShaders(const std::string& vert = "",
                      const std::string& pix = "",
                      const std::string& compute = "",
                      const std::string& geo = "");

      virtual void SetShaderDir(const std::string& dir) = 0;


      virtual void SetParameters(const std::vector<ParamPasser>& params) = 0;

      virtual void RenderShader(int indexCount) = 0;


      virtual Buffer* GetConstantBuffer(const std::string& name) final;
      virtual void AddConstantBuffer(Buffer* newBuf) final;


    protected:
      //void OutputShaderErrorMessage(ID3D10Blob*, 
      //                              HWND, 
      //                              WCHAR*);

      HashMap<std::string, Buffer*> constant_buffers_;

      ShaderType::Enum shader_type_;

      FilePath files_[ShaderType::Count];

      FilePath    vertex_file_;
      FilePath    pixel_file_;
      FilePath    compute_file_;
      FilePath    geometry_file_;
  };
}