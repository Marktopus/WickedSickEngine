#pragma once

namespace WickedSick
{
  template <typename T>
  class Factory
  {
  public:
    Factory();

    void LoadArchetypes(const std::string& dir);

    T& Make(const std::string& archetypeName);
    T& Make(const Archetype<T>& archetype);
    void Destroy(T& toDestroy);
  private:
    std::unordered_map<std::string, Archetype<T>> archetype_map_;
  };
}
