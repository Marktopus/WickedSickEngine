#pragma once

namespace WickedSick
{
  template<typename T>
  class Archetype
  {
  public:
    Archetype(const std::string& name)
              : name_(name)
    {

    }

    ~Archetype()
    {

    }

    void Load(const std::string& source)
    {
      source_ = source;
    }

    void Reload()
    {
      if (!source_.empty())
      {
        //load logic
      }
    }

    void Fill(T& myClone)
    {
      new (&myClone) T(base_object_);
    }


  private:
    std::string name_;
    std::string source_;
    T base_object_;
  };
}

