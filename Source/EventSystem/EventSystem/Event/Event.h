#pragma once

#include "Core/CoreInterface.h"

#include "EventSystemDLL.h"

namespace WickedSick
{

  class EventSystem;

  class Event
  {
  public:
    enum Type
    {
      #define RegisterType(x) x,
      #include "RegisterEventType.h"
      #undef RegisterType
      Count
    };
    

    EVENTSYSTEMDLL_API Event( const std::string& name, 
                              Type type);

    EVENTSYSTEMDLL_API std::string GetName();

    //kinda need my meta back....
    template<typename Param>
    void Add(const std::string& id, const Param& toAdd)
    {
      
    }

    //template<typename T>
    //void Set(const std::string& name, const T& type)
    //{
    //  auto& it = variables_.find(name);
    //  if (it != variables_.end())
    //  {
    //    (*it).type->Set(type);
    //  }
    //  else
    //  {
    //    variables_.insert(name, Var(type));
    //  }
    //}
    //
    //Var* Get(const std::string& name)
    //{
    //  auto& it = variables_.find(name);
    //  if (it != variables_.end())
    //  {
    //    return &((*it).type);
    //  }
    //  return nullptr;
    //}



    EVENTSYSTEMDLL_API virtual ~Event();


  private:

    //HashMap<std::string, Var> variables_;

    std::string       event_name_;
    Type              event_type_;
    int               event_ID_;

    static int        id_count_;

  protected:

    static EventSystem* event_system_;

    

  };
}
