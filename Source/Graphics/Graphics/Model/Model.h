#pragma once

#include "Math/MathInterface.h"
#include "ModelInstance.h"

#include "Renderable.h"

#include "Utility/UtilityInterface.h"
#include "Face.h"
#include "API/APIType.h"
#include "DrawType.h"

//#include "Graphics/WS_Graphics_DLL.h"

namespace WickedSick
{

  class Buffer;
  class ModelComponent;
  class Model
  {
    public:
      Model();
      virtual ~Model();

      virtual void Initialize() = 0;
      virtual void Render() = 0;

      void Set( const std::vector<Vertex>& vertexList,
                const std::vector<Face>&   faceList);      

      int GetNumIndices();
      int GetNumFaces();
      int GetNumVerts();

      void AddInstance(ModelComponent* inst);
      void RemoveInstance(ModelComponent* inst);

      virtual void BuildDebugBuffers() = 0;

      std::vector<ModelComponent*>& GetInstances();

    protected:
      Renderable buffers_;
      Renderable debug_buffers_;
      friend class DirectX;

      DrawType::Enum draw_type_;

      std::vector<ModelComponent*> instance_list_;
      std::vector<Face> face_list_;
      std::vector<Vertex> vertex_list_;
      std::vector<Vertex> face_normal_verts_;
      std::vector<Vertex> vert_normal_verts_;

  };
}
