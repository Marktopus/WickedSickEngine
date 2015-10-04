#pragma once
#include "PhysicsDLL.h"
#include "Constraint.h"
namespace WickedSick
{
  class Constraint;
  class ConstraintList
  {
    public:
      typedef std::shared_ptr<Constraint> SP_Constraint;

      PHYSICSDLL_API ConstraintList();
      PHYSICSDLL_API ~ConstraintList();
      PHYSICSDLL_API std::vector<SP_Constraint>& Get();
      PHYSICSDLL_API void push(SP_Constraint constraint);
      PHYSICSDLL_API void remove(SP_Constraint constraint);
      PHYSICSDLL_API SP_Constraint front();
      PHYSICSDLL_API SP_Constraint back();
      PHYSICSDLL_API void Update(const float& dt);
    private:
      std::vector<SP_Constraint> constraints_;
  };
}
