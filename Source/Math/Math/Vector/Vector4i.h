#pragma once
#include "MathDLL.h"
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
    MATHDLL_API Vector4i &  operator=(const Vector4i& rhs);

    // Unary negation operator, negates all components and returns a copy
    MATHDLL_API Vector4i operator-(void) const;

    // Math Operators
    MATHDLL_API Vector4i operator+(const Vector4i& rhs) const;
    MATHDLL_API Vector4i operator-(const Vector4i& rhs) const;
    MATHDLL_API Vector4i operator*(const Vector4i& rhs) const;
    MATHDLL_API Vector4i operator*(const int rhs) const;
    MATHDLL_API Vector4i operator/(const int rhs) const;
    MATHDLL_API Vector4i & operator+=(const Vector4i& rhs);
    MATHDLL_API Vector4i & operator-=(const Vector4i& rhs);
    MATHDLL_API Vector4i & operator*=(const int rhs);
    MATHDLL_API Vector4i & operator/=(const int rhs);

    // Comparison operators
    MATHDLL_API bool operator==(const Vector4i& rhs) const;
    MATHDLL_API bool operator!=(const Vector4i& rhs) const;
         
    // Linear Algebra
    MATHDLL_API float     Length(void) const;
    MATHDLL_API int       LengthSq(void) const;
    MATHDLL_API void      Negate(void);
    MATHDLL_API Vector4   GetNormalized(void); //returns a normalized version of the vector
    MATHDLL_API int       Dot(const Vector4i& rhs) const;
    MATHDLL_API Vector4i  Cross(const Vector4i& rhs) const;

    //Settor
    MATHDLL_API void Zero(void);
    MATHDLL_API void Set(int xx=0.0f, int yy=0.0f, int zz=0.0f, int ww=1.0f);

    //Helpers
    MATHDLL_API void      Print(void) const;
    MATHDLL_API Vector4i  Min(const Vector4i& rhs);
    MATHDLL_API Vector4i  Max(const Vector4i& rhs);

    MATHDLL_API Vector4   to_f();
    MATHDLL_API std::string   to_string();


    MATHDLL_API int & operator[](int index);
    MATHDLL_API int operator[](int index) const;

    int x;
    int y;
    int z;
    int w;
  };  
}
