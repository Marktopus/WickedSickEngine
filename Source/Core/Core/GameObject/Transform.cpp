#include "CorePrecompiled.h"
#include "Transform.h"

namespace WickedSick
{
  COREDLL_API Transform::Transform( GameObject*     owner,
                                    const Vector3&  pos,
                                    const Vector3&  scale,
                                    const Vector3&  rot)
                                    : pos_(pos),
                                      scale_(scale),
                                      rot_(rot),
                                      name_("Transform"),
                                      Component(CT_Transform, owner)
  {

  }
    
  COREDLL_API Transform::Transform( const Transform& rhs)
                                    : pos_(rhs.pos_),
                                      scale_(rhs.scale_),
                                      rot_(rhs.rot_),
                                      name_("Transform"),
                                      Component(CT_Transform)
  {

  }

  COREDLL_API Transform::~Transform()
  {

  }

  COREDLL_API void Transform::Initialize()
  {

  }

  COREDLL_API std::string Transform::GetName()
  {
    return name_;
  }

  COREDLL_API Vector3 Transform::GetPosition()
  {
    return pos_;
  }

  COREDLL_API void Transform::SetPosition(const Vector3& pos)
  {
    pos_ = pos;
  }

  COREDLL_API void Transform::SetPosition(float x, float y, float z)
  {
    pos_ = Vector3(x, y, z);
  }


  COREDLL_API Vector3 Transform::GetRotation()
  {
    return rot_;
  }

  COREDLL_API void Transform::SetRotation(const Vector3& rot)
  {
    rot_ = rot;
  }

  COREDLL_API void Transform::SetRotation(float x, float y, float z)
  {
    rot_ = Vector3(x, y, z);
  }

  COREDLL_API Vector3 Transform::GetScale()
  {
    return scale_;
  }

  COREDLL_API void Transform::SetScale(const Vector3& scale)
  {
    scale_.x = std::max( MINSCALE, scale.x);
    scale_.y = std::max( MINSCALE, scale.y);
    scale_.z = std::max( MINSCALE, scale.z);
  }

  COREDLL_API void Transform::SetScale(float x, float y, float z)
  {
    scale_.x = std::max( MINSCALE, x);
    scale_.y = std::max( MINSCALE, y);
    scale_.z = std::max( MINSCALE, z);
  }

  COREDLL_API void Transform::SetScale(float scale)
  {
    scale_.x = scale_.y = scale_.z = std::max( MINSCALE, scale);
  }

}