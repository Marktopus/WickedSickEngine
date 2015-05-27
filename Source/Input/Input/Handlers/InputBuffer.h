#pragma once
#include "InputInterface.h"

namespace WickedSick
{
  struct InputBuffer
  {
    InputBuffer();
    bool  last_frame_[MAX_KEYS_TEMP];
    bool  this_frame_[MAX_KEYS_TEMP];
    int   last_released_[MAX_KEYS_TEMP];
  };
}

