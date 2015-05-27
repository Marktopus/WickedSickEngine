#include "GraphicsPrecompiled.h"

#include "Model.h"

#include "Graphics/DXIncludes.h"

#include "Math/MathInterface.h"

#include "Utility/UtilityInterface.h"
#include "Debug/DebugInterface.h"

#include <fstream>
#include <cmath>

namespace WickedSick
{

  Model::Model()
  {
    loadingFunctions.insert(std::make_pair(".obj", &Model::load_obj));
  }

  Model::~Model()
  {

  }

  bool Model::Load(const std::string& modelName)
  {
    int dotIndex = modelName.find_last_of('.');
    std::string extension = modelName.substr(dotIndex, (modelName.size()) - dotIndex);
    auto& loaderFunc = loadingFunctions.find(extension);
    if (loaderFunc != loadingFunctions.end())
    {
      return (this->*(loaderFunc->second))(modelName);
    }
    ConsolePrint("Can't load file extension " + extension + " as model.");
    return false;
  }

  bool Model::load_obj(const std::string& modelName)
  {

    vertex_list_.clear();
    vertex_count_ = 0;
    face_list_.clear();
    index_count_ = 0;
    std::ifstream file(modelName, std::ifstream::beg | std::ifstream::in);
    //
    if (file.is_open())
    {
      std::string buffer;
      while (!file.eof())
      {
        std::getline(file, buffer);
        if (!buffer.empty())
        {
          int firstSpace = buffer.find_first_of(' ');
          std::string lineSig = buffer.substr(0, firstSpace - 0);

          if (lineSig == "f")
          {
            extract_face(buffer);
            index_count_ += 3;
          }
          else if (lineSig == "v")
          {
            extract_vertex(buffer);
            ++vertex_count_;
          }
          else if (lineSig == "vn")
          {

          }
          else if (lineSig == "g")
          {

          }
          else if (lineSig == "vt")
          {

          }
          else if (lineSig == "vp")
          {

          }
          else if (lineSig == "#" || lineSig == "\n" || lineSig == "")
          {
            // do nothing
          }
          else
          {
            ConsolePrint("Invalid model file (" + modelName + ")");
            return false;
          }
        }
      }
    }
    else
    {
      ConsolePrint("Model file (" + modelName + ") not found.");
      return false;
    }

    return true;
  }

  void Model::extract_vertex(std::string target)
  {
    int index;
    index = target.find_first_not_of(' ', 1);
    target = target.substr(index, target.size() - index);
    target = TrimSpaces(target);
    Vector3 toInsert;

    int innerIndex = target.find_first_of(' ') + 1;
    int innerIndex2 = target.find_last_of(' ');
    std::string first = target.substr(0, (innerIndex == std::string::npos) ? target.size() : innerIndex);
    std::string second = target.substr((innerIndex == std::string::npos) ? 0 : innerIndex, (innerIndex2 == std::string::npos) ? target.size() : (target.size() - innerIndex2));
    std::string third = target.substr((innerIndex2 == std::string::npos) ? 0 : innerIndex2, target.size());
    toInsert[0] = static_cast<float>(::atof(first.c_str()) );
    toInsert[1] = static_cast<float>(::atof(second.c_str()));
    toInsert[2] = static_cast<float>(::atof(third.c_str()) );

    vertex_list_.push_back({toInsert, Vector4(1.0f, 0.0f, 0.0f, 1.0f)});
  }

  void Model::extract_face(std::string target)
  {
    
    target = target.substr(2, target.size() - 2);

    target = TrimSpaces(target);
    
    int index;
    Vector3i toInsert;
    std::string floatBuf;
    for (int i = 0; i < 3; ++i)
    {
      index    = target.find_first_of(' ');
      floatBuf    = target.substr(0, index - 0);

      int innerIndex = floatBuf.find_first_of('/');
      int innerIndex2 = floatBuf.find_last_of('/');
      std::string first = floatBuf.substr(0, (innerIndex == std::string::npos) ? floatBuf.size() : innerIndex);
      std::string second = floatBuf.substr((innerIndex == std::string::npos) ? 0 : innerIndex + 1, (innerIndex2 == std::string::npos) ? floatBuf.size() : (floatBuf.size() - (innerIndex2 - 1)));
      std::string third = floatBuf.substr((innerIndex2 == std::string::npos) ? 0 : innerIndex2 + 1, floatBuf.size());
      toInsert[i] = ::atoi(first.c_str());
      toInsert[i] -= 1;

      index += 1;
      index = clamp(index, 0, (int)target.size());
      target = target.substr(index, target.size() - index);
    }
    face_list_.push_back(toInsert);
  }


  void Model::Initialize(ID3D11Device* device)
  {
    //gross
    Load("../Content/Models/bunny.obj");
    init_buffers(device);
    
  }

  void Model::Render(ID3D11DeviceContext* context)
  {
    render_buffers(context);
  }

  void Model::init_buffers(ID3D11Device* device)
  {
    D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	  D3D11_SUBRESOURCE_DATA vertexData, indexData;


    //SEEMS LIKE I SHOULD MAYBE MAKE A CLASS FOR THIS
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	  vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertex_count_;
	  vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	  vertexBufferDesc.CPUAccessFlags = 0;
	  vertexBufferDesc.MiscFlags = 0;
	  vertexBufferDesc.StructureByteStride = 0;

	  vertexData.pSysMem = &vertex_list_[0];
	  vertexData.SysMemPitch = 0;
	  vertexData.SysMemSlicePitch = 0;

    device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertex_buffer_);

    // Set up the description of the static index buffer.
	  indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	  indexBufferDesc.ByteWidth = sizeof(unsigned long) * index_count_;
	  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	  indexBufferDesc.CPUAccessFlags = 0;
	  indexBufferDesc.MiscFlags = 0;
	  indexBufferDesc.StructureByteStride = 0;

	  // Give the subresource structure a pointer to the index data.
	  indexData.pSysMem = &face_list_[0];
	  indexData.SysMemPitch = 0;
	  indexData.SysMemSlicePitch = 0;

    device->CreateBuffer(&indexBufferDesc, &indexData, &index_buffer_);

  }

  void Model::render_buffers(ID3D11DeviceContext* deviceContext)
  {
    unsigned int stride;
	  unsigned int offset;


	  // Set vertex buffer stride and offset.
	  stride = sizeof(Vertex); 
	  offset = 0;
    
	  // Set the vertex buffer to active in the input assembler so it can be rendered.
	  deviceContext->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);

	  // Set the index buffer to active in the input assembler so it can be rendered.
	  deviceContext->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);

	  // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  }


  int Model::GetIndexCount()
  {
    return index_count_;
  }

}