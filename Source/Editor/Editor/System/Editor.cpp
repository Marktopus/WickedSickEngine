
#include "EditorPrecompiled.h"
#include "Editor.h"
#include "Imgui/include/imgui.h"

namespace WickedSick
{

  EDITORDLL_API Editor::Editor() : System(ST_Editor)
  {

  }

  EDITORDLL_API Editor::~Editor()
  {

  }

  EDITORDLL_API bool Editor::Load()
  {

    return true;
  }

  EDITORDLL_API bool Editor::Reload()
  {
    return false;
  }

  EDITORDLL_API void Editor::Initialize()
  {
    
    
  }

  EDITORDLL_API void Editor::Update(float dt)
  {
    

  }

  EDITORDLL_API void Editor::ReceiveMessage(Event*)
  {
  }

  EDITORDLL_API void Editor::Select(GameObject * target)
  {
    selected_.insert(target->GetID());
  }

  EDITORDLL_API void Editor::Select(int id)
  {
    selected_.insert(id);
  }

  EDITORDLL_API void Editor::Deselect(GameObject * target)
  {
    selected_.erase(target->GetID());
  }

  EDITORDLL_API void Editor::Deselect(int id)
  {
    selected_.erase(id);
  }

  EDITORDLL_API void Editor::Deselect()
  {
    selected_.clear();
  }

}



