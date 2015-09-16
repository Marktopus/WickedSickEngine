///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        1/21/2014
//Description: holds function to register metadata
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#include "Precompiled.h"
#include "MetaManager.h"
#include "Metadata.h"
#include "Lua.h"


void MetaManager::RegisterMeta(Metadata* meta)
{
  getMetas()[meta->GetName()] = meta;
}

