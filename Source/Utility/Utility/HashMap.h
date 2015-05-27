#pragma once

#include <vector>

namespace WickedSick
{
  template <typename Hash, typename Type>
  class HashMap
  {
  public:
    HashMap();
    HashMap(const typename HashMap<Type>& other);
    
    //size related
    size_t size();
    size_t max_size();
    bool empty();

    //modifiers
    void clear();
    //iterator insert(const Type& elem);
    //iterator insert(iterator source);
    //iterator insert(iterator start, iterator end);
    //iterator erase(iterator


    begin

  private:
    float space_ratio_;
    float max_ratio_;
    std::vector<Type> map_;
  };
}