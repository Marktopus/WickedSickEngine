#pragma once

namespace WickedSick
{
  template<typename T>
  class Archetype
  {
  public:
    Archetype(const std::string& name);
    ~Archetype();
    void Load(const std::string& source);
    void Reload();
    void Fill(T& myClone);


  private:
    std::string name_;
    std::string source_;
  };
}