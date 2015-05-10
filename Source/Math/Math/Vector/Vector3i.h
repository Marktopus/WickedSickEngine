#pragma once
#include "Math/MathDLL.h"

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
    Vector3i MATHDLL_API & operator=(const Vector3i& rhs);

    // Unary negation operator, negates all components and returns a copy
    Vector3i  MATHDLL_API operator-(void) const;  

    // Math Operators
    Vector3i  MATHDLL_API operator+(const Vector3i& rhs) const;
    Vector3i  MATHDLL_API operator-(const Vector3i& rhs) const;
    Vector3i  MATHDLL_API operator*(const int rhs) const;
    Vector3i  MATHDLL_API operator/(const int rhs) const;
    Vector3i MATHDLL_API & operator+=(const Vector3i& rhs);
    Vector3i MATHDLL_API & operator-=(const Vector3i& rhs);
    Vector3i MATHDLL_API & operator*=(const int rhs);
    Vector3i MATHDLL_API & operator/=(const int rhs);

    // Comparison operators
    bool MATHDLL_API operator==(const Vector3i& rhs) const;
    bool MATHDLL_API operator!=(const Vector3i& rhs) const;
         
    // Linear Algebra
    float     MATHDLL_API Length(void) const;
    int       MATHDLL_API LengthSq(void) const;
    void      MATHDLL_API Negate(void);
    Vector3   MATHDLL_API GetNormalized(void); //returns a normalized version of the vector
    int       MATHDLL_API Dot(const Vector3i& rhs) const;
    Vector3i  MATHDLL_API Cross(const Vector3i& rhs) const;

    // Settors
    void MATHDLL_API Zero(void);
    void MATHDLL_API Set(int xx=0, int yy=0, int zz=0);

    // Helpers
    void      MATHDLL_API Print(void) const;
    Vector3i  MATHDLL_API Min(const Vector3i& rhs);
    Vector3i  MATHDLL_API Max(const Vector3i& rhs);

    Vector3   MATHDLL_API to_f();

    int MATHDLL_API &  operator[](int index);
    int   MATHDLL_API operator[](int index) const;

    int x;
    int y;
    int z;

  };
}

