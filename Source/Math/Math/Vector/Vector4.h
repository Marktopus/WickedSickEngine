#pragma once

#include "MathDLL.h"
namespace WickedSick
{
  struct Vector2;
  struct Vector3;
  struct Vector4i;
  struct Matrix4;

  struct Vector4
  {

    // Constructors
    MATHDLL_API Vector4(void);
    MATHDLL_API Vector4(const Vector2& rhs, float zz=0.0f, float ww=1.0f);
    MATHDLL_API Vector4(const Vector3& rhs, float ww=1.0f);
    MATHDLL_API Vector4(const Vector4& rhs);
    MATHDLL_API Vector4(float xx, float yy, float zz, float ww);

    // Assignment operator, does not need to handle self assignment
    MATHDLL_API Vector4 & operator=(const Vector4& rhs);

    // Unary negation operator, negates all components and returns a copy
    MATHDLL_API Vector4 operator-(void) const;  

    // Math Operators
    MATHDLL_API Vector4 operator+(const Vector4& rhs) const;
    MATHDLL_API Vector4 operator-(const Vector4& rhs) const;
    MATHDLL_API Vector4 operator*(const Matrix4& rhs) const; 
    MATHDLL_API Vector4 operator*(const Vector4& rhs) const;
    MATHDLL_API Vector4 operator*(const float rhs) const;
    MATHDLL_API Vector4 operator/(const float rhs) const;
    MATHDLL_API Vector4 & operator+=(const Vector4& rhs);
    MATHDLL_API Vector4 & operator-=(const Vector4& rhs);
    MATHDLL_API Vector4 & operator*=(const float rhs);
    MATHDLL_API Vector4 & operator/=(const float rhs);

    // Comparison operators
    MATHDLL_API bool operator==(const Vector4& rhs) const;
    MATHDLL_API bool operator!=(const Vector4& rhs) const;
         
    // casting operators
    friend Vector4 operator*(float f, Vector4 const & v);

    // Linear Algebra
    MATHDLL_API float   Length(void) const;
    MATHDLL_API float   LengthSq(void) const;
    MATHDLL_API void    Negate(void);
    MATHDLL_API void    Maximize(void);
    MATHDLL_API void    Minimize(void);
    MATHDLL_API Vector4 GetNormalized(void); //returns a normalized version of the vector
    MATHDLL_API void    Normalize(void);
    MATHDLL_API float   Dot(const Vector4& rhs) const;
    MATHDLL_API Vector4 Cross(const Vector4& rhs) const;
    MATHDLL_API bool    IsZero(void);

    //Settor
    MATHDLL_API void Zero(void);
    MATHDLL_API void Set(float xx=0.0f, float yy=0.0f, float zz=0.0f, float ww=1.0f);

    //Helpers
    MATHDLL_API void    Print(void) const;
    MATHDLL_API Vector4 Min(const Vector4& rhs);
    MATHDLL_API Vector4 Max(const Vector4& rhs);

    MATHDLL_API Vector4i to_i();
    MATHDLL_API std::string to_string();

    MATHDLL_API float & operator[](int index);
    MATHDLL_API float   operator[](int index) const;

    float x;
    float y;
    float z;
    float w;
  };  
}
