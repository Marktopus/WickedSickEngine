#include "ObjectFactoryPrecompiled.h"
#include "ObjectFactory.h"

#include "Messaging/MessagingInterface.h"
#include "Core/System/System.h"

namespace WickedSick
{

  OBJECTFACTORYDLL_API ObjectFactory::ObjectFactory() : System(System::ObjectFactory)
  {
  }

  OBJECTFACTORYDLL_API ObjectFactory::~ObjectFactory()
  {

  }

  OBJECTFACTORYDLL_API void ObjectFactory::Initialize()
  {

    
  }
  
  OBJECTFACTORYDLL_API bool ObjectFactory::Load()
  {
    return true;
  }
  
  OBJECTFACTORYDLL_API bool ObjectFactory::Reload()
  {
    return true;
  }
  
  OBJECTFACTORYDLL_API void ObjectFactory::Update(double dt)
  {
  }

  OBJECTFACTORYDLL_API void ObjectFactory::ReceiveMessage(Message * msg)
  {

  }


}
