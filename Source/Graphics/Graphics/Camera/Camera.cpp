#include "GraphicsPrecompiled.h"
#include "Camera.h"

namespace WickedSick
{
  GRAPHICSDLL_API Camera::Camera() : up_(Vector3(0.0f, 1.0f, 0.0f))
  {

  }

  GRAPHICSDLL_API Camera::~Camera()
  {

  }

  GRAPHICSDLL_API Vector4 Camera::GetPosition()
  {
    return pos_;
  }

  GRAPHICSDLL_API void Camera::SetPosition(const Vector4& pos)
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

  GRAPHICSDLL_API void Camera::Render()
  {
    //for now
    look_at_.Zero();
    look_at_.z = 1.0f;

    Vector3 rotation = rot_;
    rot_ *= 0.0174532925f;

    Matrix4 rotationMat;
    rotationMat.Identity();
    rotationMat.RotateX(rot_.x);
    rotationMat.RotateY(rot_.y);
    rotationMat.RotateZ(rot_.z);

    look_at_ = rotationMat * look_at_;

    Vector4 curUp = rotationMat * up_;

    look_at_ += pos_;

    Vector4 zaxis = look_at_ - pos_;
    Vector4 xaxis = up_.Cross(zaxis);
    Vector4 yaxis = zaxis.Cross(xaxis);

    view_.m[0][0] =   xaxis.x;          view_.m[0][1] =   yaxis.x;          view_.m[0][2] =   zaxis.x;          view_.m[0][3] = 0.0f;
    view_.m[1][0] =   xaxis.y;          view_.m[1][1] =   yaxis.y;          view_.m[1][2] =   zaxis.y;          view_.m[1][3] = 0.0f;
    view_.m[2][0] =   xaxis.z;          view_.m[2][1] =   yaxis.z;          view_.m[2][2] =   zaxis.z;          view_.m[2][3] = 0.0f;
    view_.m[3][0] =  -xaxis.Dot(pos_);  view_.m[3][1] =  -yaxis.Dot(pos_);  view_.m[3][2] =  -zaxis.Dot(pos_);  view_.m[3][3] = 1.0f;

  }

  GRAPHICSDLL_API Matrix4 Camera::GetViewMatrix()
  {
    return view_;
  }

}