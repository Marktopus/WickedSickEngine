#include "GraphicsPrecompiled.h"
#include "Shader/ParamTypeInfo.h"

namespace WickedSick
{
  ParamPasser::ParamPasser( const std::string& buffer,
                            const std::string& name,
                            void* data,
                            int size) 
                            : Buffer(buffer),
                              Name(name),
                              Size(size),
                              Data(nullptr)
  {
    Data = (void*)new char[size];
    memcpy(Data, data, size);
  }

  ParamPasser::ParamPasser(const ParamPasser & toCopy) 
                            : Buffer(toCopy.Buffer),
                              Name(toCopy.Name),
                              Size(toCopy.Size)
  {
    Data = (void*)new char[Size];
    memcpy(Data, toCopy.Data, Size);
  }

  ParamPasser::ParamPasser(ParamPasser && moveFrom)
                            : Buffer(moveFrom.Buffer),
                              Name(moveFrom.Name),
                              Data(moveFrom.Data),
                              Size(moveFrom.Size)
  {
  }

  void ParamPasser::Release()
  {
    if(Data)
    {
      char* todel = (char*) Data;
      delete[] todel;
    }
  }

  ParamPasser::~ParamPasser()
  {
    
  }
}

