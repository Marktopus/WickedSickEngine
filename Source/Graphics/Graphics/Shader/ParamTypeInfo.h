#pragma once


namespace WickedSick
{
  namespace InputShaderType
  {
    enum Enum
    {
      Pixel,
      Vertex,
      Geo,
      Tesselation,
      Compute
    };
  };

  namespace DataType
  {
    enum Enum
    {
      Int,
      Unsigned,
      Float,
      Typeless,
      Custom
    };
  };

  struct ParamPasser
  {
    std::string buffer;
    std::string name;
    void* data;
  };

  struct ParamTypeInfo
  {
    std::string name;
    size_t size;
    size_t offset;
  };

}
