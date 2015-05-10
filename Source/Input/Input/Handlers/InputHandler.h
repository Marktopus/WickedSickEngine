#pragma once

#include "Key.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace WickedSick
{
  enum SystemType;
  class InputHandler
  {
    public:

      InputHandler(SystemType sys);

      void Update();
      void SetActive(bool active);
      void Load(const std::string& filename);
      void Save(const std::string& filename);
      
      bool IsToggled(const std::string& identifier);
      bool IsPressed(const std::string& identifier);
      
      bool IsDoubleToggled(const std::string& identifier);
      bool IsDoublePressed(const std::string& identifier);



      std::vector<Key> get_keys(const std::string& identifier);
    private:
      //                  command     key to bind
      std::unordered_map<std::string, std::vector<Key>> inputs_;
      bool active_;
      SystemType attached_sys_;
  };
}
