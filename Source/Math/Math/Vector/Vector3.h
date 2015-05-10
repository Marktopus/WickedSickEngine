#pragma once
#include "Math/MathDLL.h"

#include <fstream>

namespace WickedSick
{
  struct Vector2;
  struct Vector3i;
  struct Matrix3;
  struct Matrix4;

  struct Vector3
  {
    // Constructors
    MATHDLL_API Vector3(void);
    MATHDLL_API Vector3(const Vector2& rhs, float zz=0.0f);
    MATHDLL_API Vector3(const Vector3& rhs);
    MATHDLL_API Vector3(float xx, float yy, float zz);

    // Assignment operator, does not need to handle self assignment
    MATHDLL_API Vector3 & operator=(const Vector3& rhs);

    // Unary negation operator, negates all components and returns a copy
    MATHDLL_API Vector3 operator-(void) const;  

    // Math Operators
    MATHDLL_API Vector3 operator+(const Vector3& rhs) const;
    MATHDLL_API Vector3 operator-(const Vector3& rhs) const;
    MATHDLL_API Vector3 operator*(const Matrix4& rhs) const;
    MATHDLL_API Vector3 operator*(const Matrix3& rhs) const;
    MATHDLL_API Vector3 operator*(const float rhs) const;
    MATHDLL_API Vector3 operator/(const float rhs) const;
    MATHDLL_API Vector3 & operator+=(const Vector3& rhs);
    MATHDLL_API Vector3 & operator-=(const Vector3& rhs);
    MATHDLL_API Vector3 & operator*=(const float rhs);
    MATHDLL_API Vector3 & operator/=(const float rhs);

    // Comparison operators
    MATHDLL_API bool operator==(const Vector3& rhs) const;
    MATHDLL_API bool operator!=(const Vector3& rhs) const;
         
    // Linear Algebra
    MATHDLL_API float   Length(void) const;
    MATHDLL_API float   LengthSq(void) const;
    MATHDLL_API void    Negate(void);
    MATHDLL_API Vector3 GetNormalized(void); //returns a normalized version of the vector
    MATHDLL_API void    Normalize(void);
    MATHDLL_API float   Dot(const Vector3& rhs) const;
    MATHDLL_API Vector3 Cross(const Vector3& rhs) const;
    MATHDLL_API bool    IsZero(void);

    // Settors
    MATHDLL_API void Zero(void);
    MATHDLL_API void Set(float xx=0.0f, float yy=0.0f, float zz=0.0f);

    // Helpers
    MATHDLL_API void    Print(void) const;
    MATHDLL_API Vector3 Min(const Vector3& rhs);
    MATHDLL_API Vector3 Max(const Vector3& rhs);

    MATHDLL_API Vector3i to_i();

    MATHDLL_API float & operator[](int index);
    MATHDLL_API float   operator[](int index) const;

    friend MATHDLL_API std::ifstream& operator>>(std::ifstream& is, Vector3& vec); 

    float x;
    float y;
    float z;
  };

  MATHDLL_API std::ifstream& operator>>(std::ifstream& is, WickedSick::Vector3& vec);
}


