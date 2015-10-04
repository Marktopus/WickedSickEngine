#include "GraphicsPrecompiled.h"
#include "Camera.h"
#include "Components/CameraComponent.h"

namespace WickedSick
{
  GRAPHICSDLL_API Camera::Camera() : source_(nullptr)
  {

  }

  GRAPHICSDLL_API Camera::~Camera()
  {

  }

  GRAPHICSDLL_API Vector3 Camera::GetPosition()
  {
    if(source_)
    {
      return static_cast<Transform*>(source_->GetSibling(CT_Transform))->GetPosition();
    }
    return pos_;
  }

  GRAPHICSDLL_API void Camera::SetPosition(const Vector3& pos)
  {
    pos_ = pos;
  }

  GRAPHICSDLL_API void Camera::SetPosition(float x, float y, float z)
  {
    pos_ = Vector3(x, y, z);
  }

  GRAPHICSDLL_API Vector3 Camera::GetRotation()
  {
    return rot_;
  }

  GRAPHICSDLL_API void Camera::SetRotation(const Vector3& rot)
  {
    rot_ = rot;
  }

  GRAPHICSDLL_API void Camera::SetRotation(float x, float y, float z)
  {
    rot_ = Vector3(x, y, z);
  }

  GRAPHICSDLL_API Vector3 Camera::GetLookAt()
  {
    if (source_)
    {
      return source_->GetLookAt();
    }
    else
    {
      //deprecated
      return look_at_;
    }
  }

  GRAPHICSDLL_API void Camera::Orient(float dt)
  {
    Vector3 upVector = Vector3(0.0f, 1.0f, 0.0f);
    Vector3 lookAt;
    Vector3 pos;
    if(source_)
    {
      lookAt = source_->GetLookAt();
      pos = static_cast<Transform*>(source_->GetSibling(CT_Transform))->GetPosition();
    }
    else // default
    {
      lookAt.Zero();
      
      pos.z = -5.0f;
      pos.y = 5.0f;
    }


    if(upVector == look_at_.GetNormalized())
    {
      upVector = Vector3(0.1f, 1.0f, 0.0f);
    }

    Vector3 rotation = rot_;
    rot_ *= 0.0174532925f;

    //we'd use this so we can rotate our axis. not relevant right now.
    Matrix4 rotationMat;
    rotationMat.Identity();
    rotationMat.RotateX(rot_.x);
    rotationMat.RotateY(rot_.y);
    rotationMat.RotateZ(rot_.z);



    //wtf is this for?
    //look_at_ = rotationMat * look_at_;

    //why am i doing this?
    //look_at_ += pos_;

    Vector3 zaxis = (lookAt - pos).GetNormalized();
    Vector3 xaxis = upVector.Cross(zaxis);
    Vector3 yaxis = zaxis.Cross(xaxis);
    xaxis.Normalize();
    yaxis.Normalize();

    view_.Identity();
    
    view_.m[0][0] = xaxis.x;  view_.m[0][1] = yaxis.x;  view_.m[0][2] = zaxis.x;  view_.m[0][3] = 0.0f;
    view_.m[1][0] = xaxis.y;  view_.m[1][1] = yaxis.y;  view_.m[1][2] = zaxis.y;  view_.m[1][3] = 0.0f;
    view_.m[2][0] = xaxis.z;  view_.m[2][1] = yaxis.z;  view_.m[2][2] = zaxis.z;  view_.m[2][3] = 0.0f;
    view_.m[3][0] = -xaxis.Dot(pos);     view_.m[3][1] = -yaxis.Dot(pos);     view_.m[3][2] = -zaxis.Dot(pos);     view_.m[3][3] = 1.0f;
    view_.Transpose();
    //return;
    //view_.m[0][0] = xaxis.x;  view_.m[0][1] = xaxis.y;  view_.m[0][2] = xaxis.z;  view_.m[0][3] = -xaxis.Dot(pos);
    //view_.m[1][0] = yaxis.x;  view_.m[1][1] = yaxis.y;  view_.m[1][2] = yaxis.z;  view_.m[1][3] = -yaxis.Dot(pos);
    //view_.m[2][0] = -zaxis.x;  view_.m[2][1] = -zaxis.y;  view_.m[2][2] = -zaxis.z;  view_.m[2][3] = -zaxis.Dot(pos);
    //view_.m[3][0] = 0.0f;     view_.m[3][1] = 0.0f;     view_.m[3][2] = 0.0f;     view_.m[3][3] = 1.0f;
    //view_.Transpose();
    //view_.Translate(Vector3(-pos_.x, -pos_.y, -pos_.z));

  }

  GRAPHICSDLL_API void Camera::SetSource(CameraComponent * source)
  {
    source_ = source;
  }

  GRAPHICSDLL_API Matrix4 Camera::GetViewMatrix()
  {
    return view_;
  }

}