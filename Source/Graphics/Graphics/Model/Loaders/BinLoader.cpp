#include "GraphicsPrecompiled.h"
#include "System/Graphics.h"
#include "BinLoader.h"
#include <fstream>
#include "Model/Model.h"
#include "Model/Vertex.h"
#include "Model/Face.h"
namespace WickedSick
{
  BinLoader::BinLoader()
  {
  }

  BinLoader::~BinLoader()
  {
  }

  Model* BinLoader::Load(const std::string & source)
  {


    std::fstream modelFile(source, std::ios::in | std::ios::binary);


    Model* newModel = Graphics::graphicsAPI->MakeModel();

    std::vector<Face> faces;
    std::vector<Vertex> vertices;
    int counts[2];

    if (modelFile.is_open())
    {
      modelFile.read((char*)counts, sizeof(int) * 2);
      faces.resize(counts[0]);
      vertices.resize(counts[1]);
      
      
      modelFile.read((char*)&faces[0], counts[0] * sizeof(WickedSick::Face));
      modelFile.read((char*)&vertices[0], counts[1] * sizeof(WickedSick::Vertex));
    }
    //for(auto& it : faces)
    //{
    //  vertices[it.indices[0]].barycentric = Vector3(1.0f, 0.0f, 0.0f);
    //  vertices[it.indices[1]].barycentric = Vector3(0.0f, 1.0f, 0.0f);
    //  vertices[it.indices[2]].barycentric = Vector3(0.0f, 0.0f, 1.0f);
    //}

    newModel->Set(vertices, faces);
    return  newModel;
  }
  
}
