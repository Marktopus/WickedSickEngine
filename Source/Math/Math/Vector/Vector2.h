#pragma once

#include "MathDLL.h"

namespace WickedSick
{
  struct Vector2i;

  struct Vector2
  {
    // Constructor
    MATHDLL_API Vector2(void);  
    MATHDLL_API Vector2(const Vector2& rhs);

    MATHDLL_API Vector2(float xx, float yy);
  
    // Assignment operator, does not need to handle self assignment
    MATHDLL_API Vector2 & operator=(const Vector2& rhs);
  
    // Unary negation operator, negates all components and returns a copy
    MATHDLL_API Vector2   operator-(void) const;  
    
    // Math Operators
    MATHDLL_API Vector2 operator+(const Vector2& rhs) const;
    MATHDLL_API Vector2 operator-(const Vector2& rhs) const;
    MATHDLL_API Vector2 operator*(const float rhs) const;
    MATHDLL_API Vector2 operator/(const float rhs) const;
    MATHDLL_API Vector2 & operator+=(const Vector2& rhs);
    MATHDLL_API Vector2 & operator-=(const Vector2& rhs);
    MATHDLL_API Vector2 & operator*=(const float rhs);
    MATHDLL_API Vector2 & operator/=(const float rhs);
  
    // Comparison operators
    MATHDLL_API bool      operator==(const Vector2& rhs) const;
    MATHDLL_API bool      operator!=(const Vector2& rhs) const;
         
    // Casting operators
    friend Vector2 operator*(float f, Vector2 const & v);

    // Linear Algebra
    MATHDLL_API float     Length(void) const;
    MATHDLL_API float     LengthSq(void) const;
    MATHDLL_API void      Negate(void);
    MATHDLL_API Vector2   GetNormalized(void);
    MATHDLL_API void      Normalize(void);
    MATHDLL_API float     Dot(const Vector2& rhs) const;
    MATHDLL_API float     Cross(const Vector2& rhs) const;
    MATHDLL_API bool      IsZero(void);

    // set all components to zero
    MATHDLL_API void      Zero(void);
    MATHDLL_API void      Set(float xx=0.0f, float yy=0.0f);

    // Helpers
    MATHDLL_API void      Print(void) const;
    MATHDLL_API Vector2   Min(const Vector2& rhs);
    MATHDLL_API Vector2   Max(const Vector2& rhs);

    MATHDLL_API Vector2i  to_i();
    MATHDLL_API std::string to_string();

    MATHDLL_API float  & operator[](int index);
    MATHDLL_API float   operator[](int index) const;
    
    float x;
    float y;
  };
}
