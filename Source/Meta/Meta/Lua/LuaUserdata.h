///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        3/4/2014
//Description: ui list implementation
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#ifndef LUA_USERDATA_H
#define LUA_USERDATA_H


namespace WickedSick
{
  /*struct LuaString
  {
    MetaDef
    char* value;
  };

  struct LuaDouble
  {
    MetaDef
    double value;
  };
  
  struct LuaFloat
  {
    MetaDef
    float value;
  };

  struct LuaBool
  {
    MetaDef
    bool value;
  };

  struct LuaLong
  {
    MetaDef
    long value;
  };

  struct LuaInt
  {
    MetaDef
    long value;
  };
  
  struct LuaUnsigned
  {
    MetaDef
    unsigned value;
  };

  struct LuaChar
  {
    MetaDef
    char value;
  };
  
  struct LuaShort
  {
    MetaDef
    short value;
  };*/

  class LuaUserdata
  {
    public:
      void SetMember(std::string name, void* value);

      void SetObject(Metadata* type, void* value);

      void SetType(Metadata* type);

      void SetIndirection(unsigned ind);

      unsigned GetIndirection();

      char* GetData();

      Metadata* GetType()
      {
        return type_;
      }
    private:
      Metadata* type_;
      unsigned indirection_;
  };

  struct LuaMemberdata
  {
    enum CBType
    {
      Get,
      Set
    };
    unsigned indirection;
    const char* name;
    Metadata* meta;
    unsigned offset;
    CBType type;
  };
}

#endif