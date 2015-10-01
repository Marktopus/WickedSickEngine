#include "GraphicsPrecompiled.h"

#include "Model.h"

#include "Math/MathInterface.h"

#include "Components/ModelComponent.h"
#include "Debugging/DebugInterface.h"

#include "Buffer/DxBuffer.h"

#include <fstream>


namespace WickedSick
{

  Model::Model()
  {
  }

  Model::~Model()
  {

  }

  void Model::Set(const std::vector<Vertex>&  vertexList,
                  const std::vector<Face>&    faceList)
  {
    vertex_list_ = vertexList;
    face_list_ = faceList;
  }

  int Model::GetNumIndices()
  {
    return face_list_.size() * 3;
  }

  int Model::GetNumFaces()
  {
    return face_list_.size();
  }

  int Model::GetNumVerts()
  {
    return vertex_list_.size();
  }

  void Model::AddInstance(ModelComponent* inst)
  {
    instance_list_.push_back(inst);
  }

  void Model::RemoveInstance(ModelComponent* inst)
  {
    for (size_t i = 0; i < instance_list_.size(); ++i)
    {
      if (instance_list_[i] == inst)
      {
        vector_remove(instance_list_, i);
        break;
      }
    }
  }

  std::vector<ModelComponent*>& Model::GetInstances()
  {
    return instance_list_;
  }

}