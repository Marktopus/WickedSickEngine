///////////////////////////////////////////////////////////////////////////
//Author:      Zhuhuii
//Date:        09/2/2014
//Description: 
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#include "MathPrecompiled.h"
#include "Vector2i.h"

#include "Vector/Vector2.h"


#include "MathUtility.h"

namespace WickedSick
{
  MATHDLL_API Vector2i::Vector2i(void) : x(0), y(0)
  {
  }

  MATHDLL_API Vector2i::Vector2i(const Vector2i& rhs) : x(rhs.x), y(rhs.y)
  {
  }

  MATHDLL_API Vector2i::Vector2i(int xx, int yy) : x(xx), y(yy)
  {
  }

  MATHDLL_API Vector2i & Vector2i::operator=(const Vector2i& rhs)
  {
    if(this != &rhs)
    {
      x = rhs.x;
      y = rhs.y;
    }
    return *this;
  }

  MATHDLL_API Vector2i Vector2i::operator-(void) const
  {
    return Vector2i(-x, -y);
  }

  MATHDLL_API Vector2i Vector2i::operator+(const Vector2i& rhs) const
  {
    return Vector2i(x + rhs.x, y + rhs.y);
  }

  MATHDLL_API Vector2i Vector2i::operator-(const Vector2i& rhs) const
  {
    return Vector2i(x - rhs.x, y - rhs.y);
  }

  MATHDLL_API Vector2i Vector2i::operator*(const int rhs) const
  {
    return Vector2i(x * rhs, y * rhs);
  }

  MATHDLL_API Vector2i Vector2i::operator/(const int rhs) const
  {
    return Vector2i(x / rhs, y / rhs);
  }


  MATHDLL_API Vector2i & Vector2i::operator+=(const Vector2i& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  MATHDLL_API Vector2i & Vector2i::operator-=(const Vector2i& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  MATHDLL_API Vector2i & Vector2i::operator*=(const int rhs)
  {
    x *= rhs;
    y *= rhs;
    return *this;
  }

  MATHDLL_API Vector2i & Vector2i::operator/=(const int rhs)
  {
    x /= rhs;
    y /= rhs;
    return *this;
  }

  MATHDLL_API bool Vector2i::operator==(const Vector2i& rhs) const
  {
    return abs(x - rhs.x) <= EPSILON &&
           abs(y - rhs.y) <= EPSILON;
  }

  MATHDLL_API bool Vector2i::operator!=(const Vector2i& rhs) const
  {
    return abs(x - rhs.x) > EPSILON ||
           abs(y - rhs.y) > EPSILON;
  }

  MATHDLL_API Vector2i operator*(int f, Vector2i const & v)
  {
    return Vector2i(v.x * f, v.y * f);
  }


  MATHDLL_API Vector2 Vector2i::GetNormalized(void) const
  {
    Vector2 floats = to_f();
    floats.Normalize();
    return floats;
  }
  
  MATHDLL_API int Vector2i::Dot(const Vector2i& rhs) const
  {
    return (x * rhs.x) + (y * rhs.y);
  }

  MATHDLL_API int Vector2i::Cross(const Vector2i& rhs) const
  {
    return (x * rhs.y) - (y * rhs.x);
  }

  MATHDLL_API void Vector2i::Zero(void)
  {
    x = y = 0;
  }

  MATHDLL_API void Vector2i::Set(int xx, int yy)
  {
    x = xx; y = yy;
  }

  MATHDLL_API void Vector2i::Negate(void)
  {
    x = -x; y = -y;
  }

  MATHDLL_API float Vector2i::Length(void) const
  {
    return sqrt(static_cast<float>(LengthSq()));
  }
  
  MATHDLL_API int Vector2i::LengthSq(void) const
  {
    return (x * x) + (y * y);
  }
  
  MATHDLL_API void Vector2i::Print(void) const
  {
    ConsolePrint(std::to_string(x) + ", " + std::to_string(y));
  }

  MATHDLL_API Vector2i Vector2i::Min(const Vector2i& rhs)
  {
    return Vector2i(std::min(x, rhs.x), std::min(y, rhs.y));
  }

  MATHDLL_API Vector2i Vector2i::Max(const Vector2i& rhs)
  {
    return Vector2i(std::max(x, rhs.x), std::max(y, rhs.y));
  }

  MATHDLL_API Vector2 Vector2i::to_f() const
  {
    return Vector2(static_cast<float>(x), static_cast<float>(y));
  }

  MATHDLL_API std::string Vector2i::to_string() const
  {
    return std::to_string(x) + std::to_string(y);
  }

  MATHDLL_API int& Vector2i::operator[](int index)
  {
    if((index > 1) || (index < 0)){__debugbreak();}
    return ((int*)this)[index];
  }

  MATHDLL_API int Vector2i::operator[](int index) const
  {
    if((index > 1) || (index < 0)){__debugbreak();}
    return ((int*)this)[index];
  }
}
