#pragma once



#include "InputBuffer.h"
#include "InputDLL.h"
#include "Utility/UtilityInterface.h"
#include "Math/MathInterface.h"
#include <set>


namespace WickedSick
{
  enum SystemType;

  struct Keybind
  {
    InputType::Enum type;
    int primaryId;
    std::set<int> ids;
    std::set<ModifierType::Enum> modifiers;
  };

  class InputHandler
  {
    public:

      INPUTDLL_API InputHandler();

      INPUTDLL_API void Update(float dt);
      INPUTDLL_API void SetActive(bool active);
      INPUTDLL_API void Load(const std::string& filename);
      INPUTDLL_API void Save(const std::string& filename);

      INPUTDLL_API bool Check(const std::string& identifier);
      INPUTDLL_API Vector2i GetMousePos();
      INPUTDLL_API int GetScrollPos();

      INPUTDLL_API void UpdateInput(const InputBuffer& buf);

      INPUTDLL_API std::vector<Keybind> get_keys(const std::string& identifier);
    private:
      //                  command     key to bind
      HashMap<std::string, Keybind> inputs_;
      std::set<std::string> active_inputs_;
      std::vector<Key> keys;
      Vector2i cur_mouse_pos_;
      int cur_wheel_pos_;
      bool current_modifiers_[ModifierType::Count];

      bool active_;
  };
}
