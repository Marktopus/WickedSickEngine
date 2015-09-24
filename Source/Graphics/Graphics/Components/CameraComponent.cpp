#include "GraphicsPrecompiled.h"
#include "CameraComponent.h"
#include "Input/InputInterface.h"

namespace WickedSick
{

  GRAPHICSDLL_API CameraComponent::CameraComponent() : Component(WickedSick::CT_CameraComponent)
  {
  }

  GRAPHICSDLL_API CameraComponent::~CameraComponent()
  {
  }

  GRAPHICSDLL_API void CameraComponent::Initialize()
  {

  }

  GRAPHICSDLL_API void CameraComponent::Update(float dt)
  {

  }

  GRAPHICSDLL_API std::string CameraComponent::GetName()
  {
    return "Camera";
  }

  GRAPHICSDLL_API void CameraComponent::SetLookAt(const Vector3& lookat)
  {
    look_at_ = lookat;
  }

  GRAPHICSDLL_API Vector3 CameraComponent::GetLookAt()
  {
    return look_at_;
  }
}
