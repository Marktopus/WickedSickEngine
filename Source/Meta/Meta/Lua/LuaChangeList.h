///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        3/4/2014
//Description: ui list implementation
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#ifndef CHANGELIST_H
#define CHANGELIST_H

namespace WickedSick
{
  struct LuaChange
  {
    LuaChange();
    LuaChange(LuaMemberdata* member, char* change);
    LuaMemberdata* member;
    char data[50];
  };

  class LuaChangeList
  {
    public:
      
      void CommitChange(LuaMemberdata* member, char* change);

      void ForceChange(LuaMemberdata* member, char* change);

      void PushChanges();

    private:
      std::unordered_map<LuaMemberdata*, LuaChange> changes_;
      void* target_;
  };
}

#endif