
#include "Core/CoreInterface.h"
#include "Graphics/GraphicsInterface.h"
#include "Window/WindowInterface.h"
#include "Input/InputInterface.h"
#include "Utility/UtilityInterface.h"
#include "Testing/TestingInterface.h"

#include "Messaging/MessagingInterface.h"



int main(void)
{
  

  WickedSick::MemoryManager<int> memory;

  WickedSick::Engine* engine = new WickedSick::Engine();

  engine->AddSystem(new WickedSick::Window());
  engine->AddSystem(new WickedSick::Graphics());
  engine->AddSystem(new WickedSick::Input());
  engine->AddSystem(new WickedSick::Messaging());
  

  engine->Initialize();

  while (engine->IsActive())
  {
    engine->Update();
  }

  delete engine;

  return 0;
}


