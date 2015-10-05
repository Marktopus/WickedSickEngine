#pragma once
#include "ParamTypeInfo.h"

#include "Math/MathInterface.h"
#include "Utility/UtilityInterface.h"

namespace WickedSick
{
  class ModelComponent;
  class Buffer;
  class Model;
  class Graphics;
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

      typedef void (*ShaderCallback)(Graphics*, ModelComponent*, std::vector<ParamPasser>&);

      Shader(const std::string& name,
             ShaderCallback callback);
      ~Shader();

      virtual void Initialize() = 0;
      virtual bool Compile(bool forceCompile = false) = 0;
      virtual void ReflectBuffers() = 0;

      virtual void Render(int indexCount) = 0;

      virtual void SetShaderDir(const std::string& dir) = 0;


      virtual void SetParameters(const std::vector<ParamPasser>& params) = 0;

      virtual void RenderShader(int indexCount) = 0;


      virtual Buffer* GetConstantBuffer(const std::string& name) final;
      virtual void AddConstantBuffer(Buffer* newBuf) final;
      virtual void AddInstance(ModelComponent* comp) final;
      virtual void ClearInstances() final;
      virtual HashMap<Model*, std::vector<ModelComponent*>>& GetInstances() final;
      virtual std::string GetName() const final;
      virtual void PrepareBuffers(ModelComponent* comp) final;

      

    protected:
      //void OutputShaderErrorMessage(ID3D10Blob*, 
      //                              HWND, 
      //                              WCHAR*);
      std::string name_;
      ShaderCallback callback_;

      HashMap<Model*, std::vector<ModelComponent*>> instance_list_;

      HashMap<std::string, Buffer*> constant_buffers_;

      ShaderType::Enum shader_type_;

      FilePath files_[ShaderType::Count];

      FilePath    vertex_file_;
      FilePath    pixel_file_;
      FilePath    compute_file_;
      FilePath    geometry_file_;
  };
}