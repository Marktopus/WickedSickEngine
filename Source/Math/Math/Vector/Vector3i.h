#pragma once
#include "MathDLL.h"

namespace WickedSick
{
  struct Vector2i;
  struct Vector3;
  struct Vector3i
  {
    // Constructors
    MATHDLL_API Vector3i(void);
    MATHDLL_API Vector3i(const Vector2i& rhs, int zz=0);
    MATHDLL_API Vector3i(const Vector3i& rhs);
    MATHDLL_API Vector3i(int xx, int yy, int zz);

    // Assignment operator, does not need to handle self assignment
    MATHDLL_API Vector3i & operator=(const Vector3i& rhs);

    // Unary negation operator, negates all components and returns a copy
    MATHDLL_API Vector3i  operator-(void) const;

    // Math Operators
    MATHDLL_API Vector3i operator+(const Vector3i& rhs) const;
    MATHDLL_API Vector3i operator-(const Vector3i& rhs) const;
    MATHDLL_API Vector3i operator*(const int rhs) const;
    MATHDLL_API Vector3i operator/(const int rhs) const;
    MATHDLL_API Vector3i & operator+=(const Vector3i& rhs);
    MATHDLL_API Vector3i & operator-=(const Vector3i& rhs);
    MATHDLL_API Vector3i & operator*=(const int rhs);
    MATHDLL_API Vector3i & operator/=(const int rhs);

    // Comparison operators
    MATHDLL_API bool operator==(const Vector3i& rhs) const;
    MATHDLL_API bool operator!=(const Vector3i& rhs) const;
         
    // Linear Algebra
    MATHDLL_API float     Length(void) const;
    MATHDLL_API int       LengthSq(void) const;
    MATHDLL_API void      Negate(void);
    MATHDLL_API Vector3   GetNormalized(void); //returns a normalized version of the vector
    MATHDLL_API int       Dot(const Vector3i& rhs) const;
    MATHDLL_API Vector3i  Cross(const Vector3i& rhs) const;

    // Settors
    MATHDLL_API void Zero(void);
    MATHDLL_API void Set(int xx=0, int yy=0, int zz=0);

    // Helpers
    MATHDLL_API void      Print(void) const;
    MATHDLL_API Vector3i  Min(const Vector3i& rhs);
    MATHDLL_API Vector3i  Max(const Vector3i& rhs);

    MATHDLL_API Vector3   to_f();
    MATHDLL_API std::string   to_string();

    MATHDLL_API int &  operator[](int index);
    MATHDLL_API int operator[](int index) const;

    int x;
    int y;
    int z;

  };
}

