///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        1/21/2014
//Description: generic member class definition/implementation
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#ifndef MEMBER_H
#define MEMBERH

#include "Precompiled.h"
#include <unordered_map>
class Metadata;
class Member
{
  public:
    Member(void) : owner_(nullptr),
                   type_(nullptr),
                   offset_(0),
                   indirection_(0)
    {

    }

    Member(std::string name, 
           Metadata* owner, 
           Metadata* type, 
           unsigned offset,
           unsigned indirection) : name_(name),
                                   owner_(owner),
                                   type_(type),
                                   offset_(offset),
                                   indirection_(indirection)
    {

    }

    const std::string& GetName() const
    {
      return name_;
    }

    Metadata* GetOwner()
    {
      return owner_;
    }

    Metadata* GetType()
    {
      return type_;
    }

    unsigned GetOffset()
    {
      return offset_;
    }

    unsigned GetIndirection()
    {
      return indirection_;
    }

  private:
    std::string name_;
    Metadata* owner_;
    Metadata* type_;
    unsigned indirection_;
    unsigned offset_;
};


#endif
