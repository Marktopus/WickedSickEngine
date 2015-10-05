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
    ParamPasser(const std::string& buffer,
                const std::string& name,
                void* data,
                int size);
    ParamPasser(const ParamPasser& toCopy);
    ParamPasser(ParamPasser&& moveFrom);
    void Release();
    ~ParamPasser();
    std::string Buffer;
    std::string Name;
    void* Data;
    int Size;
  };

  struct ParamTypeInfo
  {
    std::string name;
    size_t size;
    size_t offset;
  };

}
