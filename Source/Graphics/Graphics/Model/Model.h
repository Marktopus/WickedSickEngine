#pragma once

#include "Math/MathInterface.h"
#include "ModelInstance.h"
//#include "Graphics/WS_Graphics_DLL.h"

#include <unordered_map>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Buffer;

namespace WickedSick
{
  

  struct Vertex
  {
    Vector3 position;
    Vector4 color;
    
  };

  struct Face
  {
    std::vector<Vertex> verts;
    Vector3 normal;
  };

  class Model
  {
    public:
      Model();
      ~Model();

      bool Load(const std::string& modelName);

      void Initialize(ID3D11Device* device);
      void Render(ID3D11DeviceContext* context);
      int GetIndexCount();

    private:

      bool load_obj(const std::string& modelName);
      bool load_fbx(const std::string& modelName);

      void extract_vertex(std::string target);
      void extract_face(std::string target);

      void init_buffers(ID3D11Device* device);
      void render_buffers(ID3D11DeviceContext* context);



      typedef bool(Model::*loadFunc)(const std::string&);

      std::unordered_map<std::string, loadFunc> loadingFunctions;


      std::vector<ModelInstance> instance_list_;
      std::vector<Vector3i> face_list_;
      std::vector<Vertex> vertex_list_;

      ID3D11Buffer* vertex_buffer_;
      ID3D11Buffer* index_buffer_;
      int vertex_count_;
      int index_count_;

  };
}
