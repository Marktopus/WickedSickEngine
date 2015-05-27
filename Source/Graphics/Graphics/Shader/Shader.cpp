#include "GraphicsPrecompiled.h"
#include "Shader.h"

#include "DXIncludes.h"

namespace WickedSick
{
  Shader::Shader()
  {
	  vertex_shader_ = 0;
	  pixel_shader_ = 0;
	  layout_ = 0;
	  matrix_buffer_ = 0;
  }

  Shader::~Shader()
  {
  }

  void Shader::Initialize(ID3D11Device* device, HWND hwnd)
  {
    init_shader(device, hwnd, "../Graphics/Graphics/Shaders/color.ps", "../Graphics/Graphics/Shaders/color.vs");
  }

  void Shader::Render(ID3D11DeviceContext* deviceContext, 
                      int indexCount, 
                      const Matrix4& worldMatrix,
                      const Matrix4& viewMatrix, 
                      const Matrix4& projectionMatrix)
  {
    SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
    RenderShader(deviceContext, indexCount);
  }

  void Shader::init_shader(ID3D11Device* device,
                           HWND hwnd,
                           const std::string& pix,
                           const std::string& vert)
  {
    ID3D10Blob* errorMessage;
	  ID3D10Blob* vertexShaderBuffer;
	  ID3D10Blob* pixelShaderBuffer;
	  D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	  unsigned int numElements;
	  D3D11_BUFFER_DESC matrixBufferDesc;


	  // Initialize the pointers this function will use to null.
	  errorMessage = 0;
	  vertexShaderBuffer = 0;
	  pixelShaderBuffer = 0;
    std::wstring vertFile(vert.begin(), vert.end());
    D3DCompileFromFile (vertFile.c_str(), 
                        NULL, 
                        NULL, 
                        "ColorVertexShader", 
                        "vs_5_0",
                        D3D10_SHADER_ENABLE_STRICTNESS, 
                        0, 
				                &vertexShaderBuffer, 
                        &errorMessage);
//    ConsolePrint((char*)errorMessage->GetBufferPointer());
    std::wstring pixFie(pix.begin(), pix.end());
    D3DCompileFromFile (pixFie.c_str(), 
                        NULL, 
                        NULL, 
                        "ColorPixelShader", 
                        "ps_5_0",
                        D3D10_SHADER_ENABLE_STRICTNESS, 
                        0, 
				                &pixelShaderBuffer, 
                        &errorMessage);

    device->CreateVertexShader( vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &vertex_shader_);
    device->CreatePixelShader(  pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &pixel_shader_);

    //needs to match in class and shader
    polygonLayout[0].SemanticName = "POSITION";
	  polygonLayout[0].SemanticIndex = 0;
	  polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	  polygonLayout[0].InputSlot = 0;
	  polygonLayout[0].AlignedByteOffset = 0;
	  polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	  polygonLayout[0].InstanceDataStepRate = 0;

	  polygonLayout[1].SemanticName = "COLOR";
	  polygonLayout[1].SemanticIndex = 0;
	  polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	  polygonLayout[1].InputSlot = 0;
	  polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	  polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	  polygonLayout[1].InstanceDataStepRate = 0;

    numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	  // Create the vertex input layout.
	  device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), 
					     vertexShaderBuffer->GetBufferSize(), &layout_);


	  // Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	  vertexShaderBuffer->Release();
	  vertexShaderBuffer = 0;

	  pixelShaderBuffer->Release();
	  pixelShaderBuffer = 0;

    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	  matrixBufferDesc.ByteWidth = sizeof(MatrixBuffer);
	  matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	  matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	  matrixBufferDesc.MiscFlags = 0;
	  matrixBufferDesc.StructureByteStride = 0;

	  // Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	  device->CreateBuffer(&matrixBufferDesc, NULL, &matrix_buffer_);

  }

  void Shader::SetShaderParameters( ID3D11DeviceContext* deviceContext, 
                                    Matrix4 worldMatrix,
                                    Matrix4 viewMatrix, 
                                    Matrix4 projectionMatrix)
  {
	  D3D11_MAPPED_SUBRESOURCE mappedResource;
	  MatrixBuffer* dataPtr;
	  unsigned int bufferNumber;

    worldMatrix.Transpose();
    viewMatrix.Transpose();
    projectionMatrix.Transpose();


    deviceContext->Map(matrix_buffer_, 
                       0, 
                       D3D11_MAP_WRITE_DISCARD, 
                       0, 
                       &mappedResource);

    dataPtr = (MatrixBuffer*)mappedResource.pData;

	  // Copy the matrices into the constant buffer.
	  dataPtr->world = worldMatrix;
	  dataPtr->view = viewMatrix;
	  dataPtr->projection = projectionMatrix;

	  // Unlock the constant buffer.
	  deviceContext->Unmap(matrix_buffer_, 0);

    bufferNumber = 0;

    deviceContext->VSSetConstantBuffers(bufferNumber, 1, &matrix_buffer_);
  }

  void Shader::RenderShader(ID3D11DeviceContext* deviceContext, 
                            int indexCount)
  {
    deviceContext->IASetInputLayout(layout_);

	  // Set the vertex and pixel shaders that will be used to render this triangle.
	  deviceContext->VSSetShader(vertex_shader_, NULL, 0);
	  deviceContext->PSSetShader(pixel_shader_, NULL, 0);

	  // Render the triangle.
	  deviceContext->DrawIndexed(indexCount, 0, 0);
  }
}