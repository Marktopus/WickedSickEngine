#pragma once
#include "Key.h"

namespace WickedSick
{
  struct InputBuffer
  {
    InputBuffer();
    bool  last_frame_[Key::KeyCount];
    bool  this_frame_[Key::KeyCount];
    int   last_released_[Key::KeyCount];
  };
}

