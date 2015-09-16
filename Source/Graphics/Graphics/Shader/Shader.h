#pragma once

#include "Math/MathInterface.h"
#include "Utility\UtilityInterface.h"


namespace WickedSick
{

  class Buffer;

  class Shader
  {

    public:
	    Shader();
	    ~Shader();

	    virtual void Initialize() = 0;
      virtual bool Compile(bool forceCompile = false) = 0;

      virtual void Render(int indexCount, 
                          const Matrix4& world,
                          const Matrix4& clip,
                          const Vector3& cameraPos) = 0;

      void SetShaders(const std::string& vert = "",
                      const std::string& pix = "",
                      const std::string& compute = "",
                      const std::string& geo = "");

      virtual void SetShaderDir(const std::string& dir) = 0;


    protected:
	    //void OutputShaderErrorMessage(ID3D10Blob*, 
      //                              HWND, 
      //                              WCHAR*);

      virtual void RenderShader(int) = 0;
	    virtual void SetParameters( const Matrix4& world,
                                  const Matrix4& clip,
                                  const Vector3& cameraPos) = 0;
	    
      FilePath    vertex_file_;
      FilePath    pixel_file_;
      FilePath    compute_file_;
      FilePath    geometry_file_;

      Buffer*     matrix_buffer_;
  };
}