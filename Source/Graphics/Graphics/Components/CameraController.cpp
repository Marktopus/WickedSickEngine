#include "GraphicsPrecompiled.h"
#include "CameraController.h"
#include "CameraComponent.h"
#include "Input/InputInterface.h"

namespace WickedSick
{

  GRAPHICSDLL_API CameraController::CameraController() : Component(WickedSick::CT_CameraController)
  {
  }

  GRAPHICSDLL_API CameraController::~CameraController()
  {
  }

  GRAPHICSDLL_API void CameraController::Initialize()
  {
    Input* input = (Input*)Engine::GetCore()->GetSystem(ST_Input);
    InputHandler* handler = input->GetHandler();
    
  }

  GRAPHICSDLL_API void CameraController::Update(float dt)
  {
    Input* input = (Input*)Engine::GetCore()->GetSystem(ST_Input);
    InputHandler* handler = input->GetHandler();

    
    if (handler->Check("Rotate"))
    {
      if(last_mouse_pos_ == Vector2i(-1, -1))
      {
        last_mouse_pos_ = handler->GetMousePos();
      }
      else if(handler->GetMousePos() != last_mouse_pos_)
      {
        Vector2i curPos = handler->GetMousePos();
        Vector2 amountToRotate = (curPos - last_mouse_pos_).to_f() * dt;
        CameraComponent* cameraComp = (CameraComponent*)GetSibling(CT_CameraComponent);
        Vector3 lookAt = cameraComp->GetLookAt();
        Transform* tr = (Transform*)GetSibling(CT_Transform);
        Vector3 view = lookAt - tr->GetPosition();
        view.Normalize();
        
        
        view = RotateAround(Vector3(0, 1, 0), amountToRotate.x, view);
        view.Normalize();
        Vector3 right = Vector3(0,1,0).Cross(view);
        right.Normalize();
        view = RotateAround(right, amountToRotate.y, view);

        
        lookAt = (tr->GetPosition() + view);


        cameraComp->SetLookAt(lookAt);
        last_mouse_pos_ = Vector2i(-1, -1);
      }
    }
    else if(handler->Check("Move"))
    {
      if (last_mouse_pos_ == Vector2i(-1, -1))
      {
        last_mouse_pos_ = handler->GetMousePos();
      }
      else if (handler->GetMousePos() != last_mouse_pos_)
      {
        Vector2i curPos = handler->GetMousePos();
        Vector2 amountToMove = (curPos - last_mouse_pos_).to_f() * dt;
        CameraComponent* cameraComp = (CameraComponent*)GetSibling(CT_CameraComponent);
        Vector3 lookAt = cameraComp->GetLookAt();
        Transform* tr = (Transform*)GetSibling(CT_Transform);

        Vector3 view = lookAt - tr->GetPosition();
        view.Normalize();
        Vector3 right = Vector3(0.0f,1.0f,0.0f).Cross(view);
        right.Normalize();
        Vector3 up = view.Cross(right);
        up.Normalize();

        Vector3 pos = tr->GetPosition();
        amountToMove *= 5.0f;
        pos += right * -amountToMove.x;
        pos += up * amountToMove.y;

        lookAt += right * -amountToMove.x;
        lookAt += up * amountToMove.y;
        tr->SetPosition(pos);
        cameraComp->SetLookAt(lookAt);

        last_mouse_pos_ = Vector2i(-1, -1);
      }
    }
    else if (handler->Check("ZoomIn"))
    {
      CameraComponent* cameraComp = (CameraComponent*)GetSibling(CT_CameraComponent);
      Vector3 lookAt = cameraComp->GetLookAt();
      Transform* tr = (Transform*)GetSibling(CT_Transform);
      Vector3 view = lookAt - tr->GetPosition();
      view.Normalize();
      view *= dt;
      tr->SetPosition(tr->GetPosition() += view );
      cameraComp->SetLookAt(lookAt += view );
      
    }
    else if (handler->Check("ZoomOut"))
    {
      CameraComponent* cameraComp = (CameraComponent*)GetSibling(CT_CameraComponent);
      Vector3 lookAt = cameraComp->GetLookAt();
      Transform* tr = (Transform*)GetSibling(CT_Transform);
      Vector3 view = lookAt - tr->GetPosition();
      view.Normalize();
      view *= dt;
      tr->SetPosition(tr->GetPosition() -= view);
      cameraComp->SetLookAt(lookAt -= view);

    }
    else if (handler->GetScrollPos())
    {
      CameraComponent* cameraComp = (CameraComponent*)GetSibling(CT_CameraComponent);
      Vector3 lookAt = cameraComp->GetLookAt();
      Transform* tr = (Transform*)GetSibling(CT_Transform);
      Vector3 view = lookAt - tr->GetPosition();
      view.Normalize();
      view *= dt;
      tr->SetPosition(tr->GetPosition() + view * (float)handler->GetScrollPos());
      cameraComp->SetLookAt(lookAt + view * (float)handler->GetScrollPos());

    }
    else
    {
      last_mouse_pos_ = Vector2i(-1, -1);
    }

    
  }

  GRAPHICSDLL_API std::string CameraController::GetName()
  {
    return "CameraController";
  }
}
