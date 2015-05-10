///////////////////////////////////////////////////////////////////////////
//Author:      Mark, Nathan Park
//Date:        4/4/2014
//Description: file io includes
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#include "MathPrecompiled.h"
#include "Vector3.h"

#include "Vector/Vector2.h"
#include "Vector/Vector3i.h"

#include "Matrix/Matrix4.h"
#include "Matrix/Matrix3.h"


#include "Math/MathUtility.h"
namespace WickedSick
{
MATHDLL_API   Vector3::Vector3(void) : 
    x(0.0f), y(0.0f), z(0.0f)
  {
  }

MATHDLL_API   Vector3::Vector3(const Vector2& rhs, float zz) : 
    x(rhs.x), y(rhs.y), z(zz)
  {
  }

MATHDLL_API   Vector3::Vector3(const Vector3& rhs) : 
    x(rhs.x), y(rhs.y), z(rhs.z)
  {
    
  }

MATHDLL_API   Vector3::Vector3(float xx, float yy, float zz) : 
    x(xx), y(yy), z(zz)
  {
  }

  MATHDLL_API Vector3  & Vector3::operator=(const Vector3& rhs)
  {
    if(this != &rhs)
    {
      x = rhs.x;
      y = rhs.y;
      z = rhs.z;
    }
    return *this;
  }

  MATHDLL_API Vector3 Vector3::operator-(void) const
  {
    return Vector3(-x, -y, -z);
  }

  MATHDLL_API Vector3 Vector3::operator+(const Vector3& rhs) const
  {
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  MATHDLL_API Vector3 Vector3::operator-(const Vector3& rhs) const
  {
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  MATHDLL_API Vector3 Vector3::operator*(const float rhs) const
  {
    return Vector3(x * rhs, y * rhs, z * rhs);
  }

  MATHDLL_API Vector3 Vector3::operator/(const float rhs) const
  {
    return Vector3(x / rhs, y / rhs, z / rhs);
  }


  MATHDLL_API Vector3  & Vector3::operator+=(const Vector3& rhs)
  {
    x += rhs.x;
    y += rhs.y; 
    z += rhs.z;
    return *this;
  }

  MATHDLL_API Vector3  & Vector3::operator-=(const Vector3& rhs)
  {
    x -= rhs.x;
    y -= rhs.y; 
    z -= rhs.z;
    return *this;
  }

  MATHDLL_API Vector3  & Vector3::operator*=(const float rhs)
  {
    x *= rhs;
    y *= rhs; 
    z *= rhs;
    return *this;
  }

  MATHDLL_API Vector3  & Vector3::operator/=(const float rhs)
  {
    x /= rhs;
    y /= rhs; 
    z /= rhs;
    return *this;
  }

  MATHDLL_API bool Vector3::operator==(const Vector3& rhs) const
  {
    return  abs(x - rhs.x) <= EPSILON &&
            abs(y - rhs.y) <= EPSILON &&
            abs(z - rhs.z) <= EPSILON;
  }

  MATHDLL_API bool Vector3::operator!=(const Vector3& rhs) const
  {
    return  abs(x - rhs.x) > EPSILON ||
            abs(y - rhs.y) > EPSILON ||
            abs(z - rhs.z) > EPSILON;
  }

  MATHDLL_API Vector3 Vector3::operator*(const Matrix4& rhs) const
  {
    float w = x * rhs.m03 + y * rhs.m13 + z * rhs.m23 + rhs.m33;
  
    // guard against divide by zero
    float invW = 0;
    if( w ) invW = 1.0f / w;
  
    return Vector3(x * rhs.m00 + y * rhs.m10 + z * rhs.m20 + rhs.m30,
                   x * rhs.m01 + y * rhs.m11 + z * rhs.m21 + rhs.m31,
                   x * rhs.m02 + y * rhs.m12 + z * rhs.m22 + rhs.m32) * invW;
  }
  
  MATHDLL_API Vector3 Vector3::operator*(const Matrix3& rhs) const
  {
    return Vector3( x * rhs.m00 + y * rhs.m10 + z * rhs.m20,
                    x * rhs.m01 + y * rhs.m11 + z * rhs.m21,
                    x * rhs.m02 + y * rhs.m12 + z * rhs.m22);
  }

  MATHDLL_API float Vector3::Length(void) const
  {
    return sqrt(LengthSq());
  }


  MATHDLL_API float Vector3::LengthSq(void) const
  {
    return (x * x) + (y * y) + (z * z);
  }

  MATHDLL_API void Vector3::Negate(void)
  {
    x = -x; y = -y; z = -z;
  }

  MATHDLL_API Vector3 Vector3::GetNormalized()
  {
    float len = Length();
    if(len == 0)
    {
      return Vector3();
    }
    return Vector3(x / len, y / len, z / len);
  }

  MATHDLL_API void Vector3::Normalize()
  {
    float len = Length();
    if(len == 0.0f)
    {
      //Warn("error: normalizing a zero vector");
      Zero();
      return;
    }

    x /= len;
    y /= len;
    z /= len;
  }

  MATHDLL_API float Vector3::Dot(const Vector3& rhs) const
  {
    return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
  }

  MATHDLL_API Vector3 Vector3::Cross(const Vector3& rhs) const
  {
    return Vector3( y * rhs.z - z * rhs.y,
                    z * rhs.x - x * rhs.z,
                    x * rhs.y - y * rhs.x);
  }

  MATHDLL_API bool Vector3::IsZero(void)
  {
    if(x == 0.0f && y == 0.0f && z == 0.0f) return true;
    else                                    return false;
  }

  MATHDLL_API void Vector3::Zero(void)
  {
    x = y = z = 0.0f;
  }

  MATHDLL_API void Vector3::Print(void) const
  {
    //ConsolePrint(std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z));
  }

  MATHDLL_API Vector3 Vector3::Min(const Vector3 & rhs)
  {
    return Vector3(std::min(x, rhs.x), std::min(y, rhs.y), std::min(z, rhs.z));
  }

  MATHDLL_API Vector3 Vector3::Max(const Vector3 & rhs)
  {
    return Vector3(std::max(x, rhs.x), std::max(y, rhs.y), std::max(z, rhs.z));
  }


  MATHDLL_API Vector3i Vector3::to_i()
  {
    return Vector3i(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z));
  }

  MATHDLL_API float  & Vector3::operator [](int index)
  {
    if((index > 2) || (index < 0)){__debugbreak();}
    return ((float*)this)[index];
  }

  MATHDLL_API float Vector3::operator[](int index) const
  {
    if((index > 2) || (index < 0)){__debugbreak();}
    return ((float*)this)[index];
  }
  MATHDLL_API std::ifstream& operator>>(std::ifstream& is, Vector3& vec)
  {
    is >> vec.x;
    is >> vec.y;
    is >> vec.z;
    return is;
  }
}

