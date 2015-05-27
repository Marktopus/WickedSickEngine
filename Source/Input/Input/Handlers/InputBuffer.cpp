///////////////////////////////////////////////////////////////////////////////
// Author(s)  : Mark
// Created    : 10/12/2014
// Description: 
// All Content © 2014 DigiPen (USA) Corporation, All Rights Reserved
///////////////////////////////////////////////////////////////////////////////
#include "InputPrecompiled.h"
#include "InputBuffer.h"


namespace WickedSick
{
  InputBuffer::InputBuffer()
  {
    memset(&last_frame_[0],     0, MAX_KEYS_TEMP * sizeof(last_frame_   [0]));
    memset(&this_frame_[0],     0, MAX_KEYS_TEMP * sizeof(this_frame_   [0]));
    memset(&last_released_[0],  0, MAX_KEYS_TEMP * sizeof(last_released_[0]));
  }
}
