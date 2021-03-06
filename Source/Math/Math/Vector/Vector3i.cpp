
#include "MathPrecompiled.h"
#include "Vector3i.h"


#include "Vector/Vector2i.h"
#include "Vector/Vector3.h"
#include "MathUtility.h"

namespace WickedSick
{
  MATHDLL_API Vector3i::Vector3i(void) : 
    x(0), y(0), z(0)
  {
  }

  MATHDLL_API Vector3i::Vector3i(const Vector2i& rhs, int zz) : 
    x(rhs.x), y(rhs.y), z(zz)
  {
  }

  MATHDLL_API Vector3i::Vector3i(const Vector3i& rhs) : 
    x(rhs.x), y(rhs.y), z(rhs.z)
  {
  }

  MATHDLL_API Vector3i::Vector3i(int xx, int yy, int zz) : 
    x(xx), y(yy), z(zz)
  {
  }

  Vector3i MATHDLL_API & Vector3i::operator=(const Vector3i& rhs)
  {
    if(this != &rhs)
    {
      x = rhs.x;
      y = rhs.y;
      z = rhs.z;
    }
    return *this;
  }

  Vector3i MATHDLL_API Vector3i::operator-(void) const
  {
    return Vector3i(-x, -y, -z);
  }

  Vector3i MATHDLL_API Vector3i::operator+(const Vector3i& rhs) const
  {
    return Vector3i(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  Vector3i MATHDLL_API Vector3i::operator-(const Vector3i& rhs) const
  {
    return Vector3i(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  Vector3i MATHDLL_API Vector3i::operator*(const int rhs) const
  {
    return Vector3i(x * rhs, y * rhs, z * rhs);
  }

  Vector3i MATHDLL_API Vector3i::operator/(const int rhs) const
  {
    return Vector3i(x / rhs, y / rhs, z / rhs);
  }


  Vector3i MATHDLL_API & Vector3i::operator+=(const Vector3i& rhs)
  {
    x += rhs.x;
    y += rhs.y; 
    z += rhs.z;
    return *this;
  }

  Vector3i MATHDLL_API & Vector3i::operator-=(const Vector3i& rhs)
  {
    x -= rhs.x;
    y -= rhs.y; 
    z -= rhs.z;
    return *this;
  }

  Vector3i MATHDLL_API & Vector3i::operator*=(const int rhs)
  {
    x *= rhs;
    y *= rhs; 
    z *= rhs;
    return *this;
  }

  Vector3i MATHDLL_API & Vector3i::operator/=(const int rhs)
  {
    x /= rhs;
    y /= rhs; 
    z /= rhs;
    return *this;
  }

  bool MATHDLL_API Vector3i::operator==(const Vector3i& rhs) const
  {
    return  abs(x - rhs.x) <= EPSILON &&
            abs(y - rhs.y) <= EPSILON &&
            abs(z - rhs.z) <= EPSILON;
  }

  bool MATHDLL_API Vector3i::operator!=(const Vector3i& rhs) const
  {
    return  abs(x - rhs.x) > EPSILON ||
            abs(y - rhs.y) > EPSILON ||
            abs(z - rhs.z) > EPSILON;
  }

  float MATHDLL_API Vector3i::Length(void) const
  {
    return sqrt(static_cast<float>(LengthSq()));
  }


  int MATHDLL_API Vector3i::LengthSq(void) const
  {
    return (x * x) + (y * y) + (z * z);
  }

  Vector3 MATHDLL_API Vector3i::GetNormalized()
  {
    Vector3 floats = to_f();
    floats.Normalize();
    return floats;
  }

  int MATHDLL_API Vector3i::Dot(const Vector3i& rhs) const
  {
    return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
  }

  Vector3i MATHDLL_API Vector3i::Cross(const Vector3i& rhs) const
  {
    return Vector3i( y * rhs.z - z * rhs.y,
                    z * rhs.x - x * rhs.z,
                    x * rhs.y - y * rhs.x);
  }

  void MATHDLL_API Vector3i::Zero(void)
  {
    x = y = z = 0;
  }

  void MATHDLL_API Vector3i::Print(void) const
  {
    ConsolePrint(std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z));
  }

  Vector3i MATHDLL_API Vector3i::Min(const Vector3i & rhs)
  {
    return Vector3i(std::min(x, rhs.x), std::min(y, rhs.y), std::min(z, rhs.z));
  }

  Vector3i MATHDLL_API Vector3i::Max(const Vector3i & rhs)
  {
    return Vector3i(std::max(x, rhs.x), std::max(y, rhs.y), std::max(z, rhs.z));
  }

  Vector3 MATHDLL_API Vector3i::to_f()
  {
    return Vector3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
  }

  MATHDLL_API std::string Vector3i::to_string()
  {
    return std::to_string(x) + std::to_string(y) + std::to_string(z);
  }

  int MATHDLL_API & Vector3i::operator[](int index)
  {
    if((index > 2) || (index < 0)){__debugbreak();}
    return ((int*)this)[index];
  }

  int MATHDLL_API Vector3i::operator[](int index) const
  {
    if((index > 2) || (index < 0)){__debugbreak();}
    return ((int*)this)[index];
  }
}
