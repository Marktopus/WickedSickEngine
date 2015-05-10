///////////////////////////////////////////////////////////////////////////
//Author:      Zhuhuii
//Date:        09/2/2014
//Description:
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#include "MathPrecompiled.h"
#include "Vector4i.h"
#include "Vector3i.h"
#include "Vector2i.h"

#include "Vector4.h"

#include "Math/MathUtility.h"

namespace WickedSick
{
  MATHDLL_API Vector4i::Vector4i(void) : 
    x(0), y(0), z(0), w(0)
  {
  }

  MATHDLL_API Vector4i::Vector4i(const Vector2i& rhs, int zz, int ww) : 
    x(rhs.x), y(rhs.y), z(zz), w(ww)
  {
  }

  MATHDLL_API Vector4i::Vector4i( const Vector3i& rhs, int ww ) : 
    x(rhs.x), y(rhs.y), z(rhs.z), w(ww)
  {
  }

  MATHDLL_API Vector4i::Vector4i(const Vector4i& rhs) : 
    x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
  {
  }

  MATHDLL_API Vector4i::Vector4i(int xx, int yy, int zz, int ww) : 
    x(xx), y(yy), z(zz), w(ww)
  {
  }

  Vector4i MATHDLL_API & Vector4i::operator=(const Vector4i& rhs)
  {
    if(this != &rhs)
    {
      x = rhs.x;
      y = rhs.y;
      z = rhs.z;
      w = rhs.w;
    }
    return *this;
  }

  Vector4i MATHDLL_API Vector4i::operator-(void) const
  {
    return Vector4i(-x, -y, -z, -w);
  }

  Vector4i MATHDLL_API Vector4i::operator+(const Vector4i& rhs) const
  {
    return Vector4i( x + rhs.x,
                    y + rhs.y, 
                    z + rhs.z,
                    w + rhs.w);
  }

  Vector4i MATHDLL_API Vector4i::operator-(const Vector4i& rhs) const
  {
    return Vector4i( x - rhs.x,
                    y - rhs.y, 
                    z - rhs.z,
                    w - rhs.w);
  }

  Vector4i MATHDLL_API Vector4i::operator*(const int rhs) const
  {
    return Vector4i( x * rhs,
                    y * rhs, 
                    z * rhs,
                    w * rhs);
  }

  Vector4i MATHDLL_API Vector4i::operator*(const Vector4i& rhs) const
  {
    return Vector4i( x * rhs.x,
                    y * rhs.y, 
                    z * rhs.z, 
                    w * rhs.w);
  }

  Vector4i MATHDLL_API Vector4i::operator/(const int rhs) const
  {
    return Vector4i( x / rhs,
                    y / rhs, 
                    z / rhs, 
                    w / rhs);
  }


  Vector4i MATHDLL_API & Vector4i::operator+=(const Vector4i& rhs)
  {
    x += rhs.x;
    y += rhs.y; 
    z += rhs.z;
    w += rhs.w;
    return *this;
  }

  Vector4i MATHDLL_API & Vector4i::operator-=(const Vector4i& rhs)
  {
    x -= rhs.x;
    y -= rhs.y; 
    z -= rhs.z;
    w -= rhs.w;
    return *this;
  }

  Vector4i MATHDLL_API & Vector4i::operator*=(const int rhs)
  {
    x *= rhs;
    y *= rhs; 
    z *= rhs;
    w *= rhs;
    return *this;
  }

  Vector4i MATHDLL_API & Vector4i::operator/=(const int rhs)
  {
    if(rhs == 0)
    {
      Zero();
    }
    else
    {
      x /= rhs;
      y /= rhs; 
      z /= rhs;
      w /= rhs;
    }
    return *this;
  }

  bool MATHDLL_API Vector4i::operator==(const Vector4i& rhs) const
  {
    return  abs(x - rhs.x) <= EPSILON &&
            abs(y - rhs.y) <= EPSILON &&
            abs(z - rhs.z) <= EPSILON &&
            abs(w - rhs.w) <= EPSILON;
  }

  bool MATHDLL_API Vector4i::operator!=(const Vector4i& rhs) const
  {
    return  abs(x - rhs.x) > EPSILON ||
            abs(y - rhs.y) > EPSILON ||
            abs(z - rhs.z) > EPSILON ||
            abs(w - rhs.w) > EPSILON;
  }

  float MATHDLL_API Vector4i::Length(void) const
  {
    return sqrt(static_cast<float>(LengthSq()));
  }

  int MATHDLL_API Vector4i::LengthSq(void) const
  {
    return x * x + y * y + z * z;
  }

  void MATHDLL_API Vector4i::Negate(void)
  {
    x = -x; y = -y; z = -z; w = -w;
  }

  Vector4 MATHDLL_API Vector4i::GetNormalized(void)
  {
    Vector4 floats = to_f();
    floats.Normalize();
    return floats;
  }

  int MATHDLL_API Vector4i::Dot(const Vector4i& rhs) const
  {
    return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);// + (w * rhs.w);
  }

  Vector4i MATHDLL_API Vector4i::Cross(const Vector4i& rhs) const
  {
    return Vector4i(y * rhs.z - z * rhs.y,
                    z * rhs.x - x * rhs.z,
                    x * rhs.y - y * rhs.x, 
                    1);
  }

  void MATHDLL_API Vector4i::Zero(void)
  {
    x = y = z = 0;
  }

  void MATHDLL_API Vector4i::Set(int xx, int yy, int zz, int ww)
  {
    x = xx; y = yy; z = zz; w = ww;
  }

  void MATHDLL_API Vector4i::Print(void) const
  {
    //ConsolePrint(std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w));
  }

  Vector4i MATHDLL_API Vector4i::Min(const Vector4i& rhs)
  {
    return Vector4i(std::min(x, rhs.x), std::min(y, rhs.y), std::min(z, rhs.z), std::min(w, rhs.w));
  }

  Vector4i MATHDLL_API Vector4i::Max(const Vector4i& rhs)
  {
    return Vector4i(std::max(x, rhs.x), std::max(y, rhs.y), std::max(z, rhs.z), std::max(w, rhs.w));
  }

  Vector4 MATHDLL_API Vector4i::to_f()
  {
    return Vector4(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w));
  }

  int MATHDLL_API &  Vector4i::operator[](int index)
  {
    if((index > 3) || (index < 0)){__debugbreak();}
    return ((int*)this)[index];
  }

  int MATHDLL_API Vector4i::operator[](int index) const
  {
    if((index > 3) || (index < 0)){__debugbreak();}
    return ((int*)this)[index];
  }
}