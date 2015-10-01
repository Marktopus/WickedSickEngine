#pragma once
#include "EditorDLL.h"
#include "Core/CoreInterface.h"

namespace WickedSick
{
  class GameObject;
  class Event;
  class Editor : public System
  {
    public:
      EDITORDLL_API Editor();
      EDITORDLL_API ~Editor();

      EDITORDLL_API void Initialize() override;
      EDITORDLL_API bool Load() override;
      EDITORDLL_API bool Reload() override;
      EDITORDLL_API void Update(float dt) override;
      EDITORDLL_API void ReceiveMessage(Event* letter) override;

      EDITORDLL_API void Select(GameObject* target);
      EDITORDLL_API void Select(int id);
      EDITORDLL_API void Deselect(GameObject* target);
      EDITORDLL_API void Deselect(int id);
      EDITORDLL_API void Deselect();
    private:
      void draw_ui();
      std::set<int> selected_;
  };
}
