#pragma once

#include "CoreDLL.h"

namespace WickedSick
{
  class FrameController
  {
  public:
    COREDLL_API FrameController();
    COREDLL_API ~FrameController();
    void    COREDLL_API Step();
    void    COREDLL_API Update();
    void    COREDLL_API SetTimeStep(double time_step);
    double  COREDLL_API GetTimeStep();
    double  COREDLL_API GetFrameTime();
  private:
    LARGE_INTEGER last_time_;
    LARGE_INTEGER clocks_per_cycle_;
    
    double        max_accumulator_;
    double        frame_time_;
    double        time_step_;
    double        accumulator_;
    double        last_elapsed_;
    double        elapsed_;
    short         frame_count_;
    short         fps_;
  };
}
