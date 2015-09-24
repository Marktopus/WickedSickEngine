#pragma once
#include "InputPrecompiled.h"
#include "InputDLL.h"
#include "Math/MathInterface.h"
#include "InputEnums.h"

namespace WickedSick
{
  struct Key
  {
    INPUTDLL_API Key();
    int key;
    float sinceReleased;
    bool inputType[InputType::Count];
  };

  struct InputBuffer
  {
    INPUTDLL_API InputBuffer();
    INPUTDLL_API bool Get(int index);
    INPUTDLL_API void Set(int index, bool value);
    bool down[MaxKeys];
    bool current_modifiers_[ModifierType::Count];
    Vector2i mousePos;
    int wheelChange;
  };
}

