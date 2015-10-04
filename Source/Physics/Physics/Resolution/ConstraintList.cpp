
#include "PhysicsPrecompiled.h"
#include "ConstraintList.h"
#include "Constraint.h"

namespace WickedSick
{
  PHYSICSDLL_API ConstraintList::ConstraintList()
  {
  }
  
  PHYSICSDLL_API ConstraintList::~ConstraintList()
  {
  }
  
  PHYSICSDLL_API std::vector<ConstraintList::SP_Constraint>& ConstraintList::Get()
  { 
    return constraints_; 
  }
  
  PHYSICSDLL_API void ConstraintList::push(SP_Constraint constraint)
  { 
    constraints_.push_back(constraint); 
  }
  
  PHYSICSDLL_API ConstraintList::SP_Constraint ConstraintList::front()
  { 
    return constraints_.front(); 
  }
  
  PHYSICSDLL_API ConstraintList::SP_Constraint ConstraintList::back()
  { 
    return constraints_.back(); 
  }

  PHYSICSDLL_API void ConstraintList::Update(const float& dt)
  {
    for(unsigned i = 0; i < constraints_.size(); ++i)
    {

      if(!constraints_[i]->IsSatisfied())
      {
        constraints_[i]->Iterate(dt);
      }

      // this code is never run? //need to work on this sometime....
      //else
      //{
      //  vector_remove(constraints_, i);
      //  if(!constraints_.size())
      //  {
      //    break;
      //  }
      //  //we need to iterate the current one as well
      //}
    }
  }
}
