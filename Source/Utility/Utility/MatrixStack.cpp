#include "UtilityPrecompiled.h"
#include "MatrixStack.h"

namespace WickedSick
{
  UTILITYDLL_API MatrixStack::MatrixStack() : current_index_(0)
  {
    mat_stack_.resize(10, Matrix4().Identity());
  }

  UTILITYDLL_API Matrix4 MatrixStack::Top()
  {
    return mat_stack_[current_index_];
  }

  UTILITYDLL_API void MatrixStack::Push(const Matrix4& toPush)
  {
    current_index_ += 1;
    if (mat_stack_.size() == current_index_)
    {
      mat_stack_.push_back(toPush * mat_stack_[current_index_ - 1]);
    }
    else
    {
      mat_stack_[current_index_] = toPush * mat_stack_[current_index_ - 1];
    }
  }

  UTILITYDLL_API Matrix4 MatrixStack::Pop(int num)
  {
    num = abs(num);
    current_index_ -= std::min(num, current_index_);
    return mat_stack_[current_index_ + 1];
  }
}
