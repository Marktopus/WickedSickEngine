#pragma once
#include "Math/MathDLL.h"
namespace WickedSick
{
  struct Vector2i;
  struct Vector3i;
  struct Vector4;

  struct Vector4i
  {
    // Constructors
    MATHDLL_API Vector4i(void);
    MATHDLL_API Vector4i(const Vector2i& rhs, int zz=0, int ww=1);
    MATHDLL_API Vector4i(const Vector3i& rhs, int ww=1);
    MATHDLL_API Vector4i(const Vector4i& rhs);
    MATHDLL_API Vector4i(int xx, int yy, int zz, int ww);

    // Assignment operator, does not need to handle self assignment
    Vector4i MATHDLL_API &  operator=(const Vector4i& rhs);

    // Unary negation operator, negates all components and returns a copy
    Vector4i  MATHDLL_API operator-(void) const;  

    // Math Operators
    Vector4i  MATHDLL_API operator+(const Vector4i& rhs) const;
    Vector4i  MATHDLL_API operator-(const Vector4i& rhs) const;
    Vector4i  MATHDLL_API operator*(const Vector4i& rhs) const;
    Vector4i  MATHDLL_API operator*(const int rhs) const;
    Vector4i  MATHDLL_API operator/(const int rhs) const;
    Vector4i MATHDLL_API & operator+=(const Vector4i& rhs);
    Vector4i MATHDLL_API & operator-=(const Vector4i& rhs);
    Vector4i MATHDLL_API & operator*=(const int rhs);
    Vector4i MATHDLL_API & operator/=(const int rhs);

    // Comparison operators
    bool MATHDLL_API operator==(const Vector4i& rhs) const;
    bool MATHDLL_API operator!=(const Vector4i& rhs) const;
         
    // Linear Algebra
    float     MATHDLL_API Length(void) const;
    int       MATHDLL_API LengthSq(void) const;
    void      MATHDLL_API Negate(void);
    Vector4   MATHDLL_API GetNormalized(void); //returns a normalized version of the vector
    int       MATHDLL_API Dot(const Vector4i& rhs) const;
    Vector4i  MATHDLL_API Cross(const Vector4i& rhs) const;

    //Settor
    void MATHDLL_API Zero(void);
    void MATHDLL_API Set(int xx=0.0f, int yy=0.0f, int zz=0.0f, int ww=1.0f);

    //Helpers
    void      MATHDLL_API Print(void) const;
    Vector4i  MATHDLL_API Min(const Vector4i& rhs);
    Vector4i  MATHDLL_API Max(const Vector4i& rhs);

    Vector4   MATHDLL_API to_f();

    int MATHDLL_API & operator[](int index);
    int MATHDLL_API operator[](int index) const;

    int x;
    int y;
    int z;
    int w;
  };  
}
