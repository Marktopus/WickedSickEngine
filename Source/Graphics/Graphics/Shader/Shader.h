#pragma once

#include "Math/MathInterface.h"

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
struct ID3D11DeviceContext;
struct ID3D11Device;
struct ID3D11Buffer;
struct ID3D10Blob;

namespace WickedSick
{

  class Shader
  {

    public:
	    Shader();
	    ~Shader();

	    void Initialize(ID3D11Device* device, 
                      HWND hwnd);
	    void Render(ID3D11DeviceContext* context, 
                  int, 
                  const Matrix4&, 
                  const Matrix4&, 
                  const Matrix4&);

    private:
	    void init_shader(ID3D11Device* device, 
                       HWND hwnd, 
                       const std::string& pix, 
                       const std::string& vert);
	    void OutputShaderErrorMessage(ID3D10Blob*, 
                                    HWND, 
                                    WCHAR*);

      void RenderShader(ID3D11DeviceContext*, 
                        int);

	    void SetShaderParameters(ID3D11DeviceContext*, 
                               Matrix4, 
                               Matrix4, 
                               Matrix4);
	     


      struct MatrixBuffer
	    {
		    Matrix4 world;
		    Matrix4 view;
		    Matrix4 projection;
	    };

	    ID3D11VertexShader* vertex_shader_;
	    ID3D11PixelShader* pixel_shader_;
	    ID3D11InputLayout* layout_;
	    ID3D11Buffer* matrix_buffer_;
  };
}