#pragma once

#include "Math/MathInterface.h"
#include "UtilityDLL.h"

#include <vector>

namespace WickedSick
{
  class MatrixStack
  {
  public:
    UTILITYDLL_API MatrixStack();
    UTILITYDLL_API Matrix4 Top();
    UTILITYDLL_API void Push(const Matrix4& toPush);
    UTILITYDLL_API Matrix4 Pop(int num = 1);
  private:
    int current_index_;
    std::vector<Matrix4> mat_stack_;
  };
}
