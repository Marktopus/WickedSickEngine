#include "GraphicsPrecompiled.h"
#include "ModelComponent.h"

#include "Model/Model.h"
#include "Core/CoreInterface.h"
#include "System/Graphics.h"

namespace WickedSick
{
  GRAPHICSDLL_API ModelComponent::ModelComponent( const std::string& model,
                                                  GameObject* owner)  : name_("ModelComponent"),
                                                                        model_(model),
                                                                        base_(nullptr),
                                                                        Component(CT_ModelComponent, owner)
  {
    
  }

  GRAPHICSDLL_API ModelComponent::~ModelComponent()
  {

  }

  GRAPHICSDLL_API std::string ModelComponent::GetName()
  {
    return name_;
  }

  GRAPHICSDLL_API void ModelComponent::Initialize()
  {
    Engine* core = Engine::GetCore();
    Graphics* gSys = (Graphics*)core->GetSystem(ST_Graphics);
    base_ = gSys->GetModel(model_);
    if (base_)
    {
      base_->AddInstance(this);
    }
  }

  GRAPHICSDLL_API void ModelComponent::Update(float dt)
  {
    //nothing
  }

  GRAPHICSDLL_API void ModelComponent::Destroy()
  {
    base_->RemoveInstance(this);
  }

  GRAPHICSDLL_API void ModelComponent::SetModel(const std::string & model)
  {
    model_ = model;
  }
}