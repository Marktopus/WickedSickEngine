#pragma once

#include "Math/MathDLL.h"

namespace WickedSick
{
  struct Vector2;

  struct Vector2i
  {

    // Constructor
    MATHDLL_API Vector2i(void);  
    MATHDLL_API Vector2i(const Vector2i& rhs);
    MATHDLL_API Vector2i(int xx, int yy);
  
    // Assignment operator, does not need to handle self assignment
    MATHDLL_API Vector2i & operator=(const Vector2i& rhs);
  
    // Unary negation operator, negates all components and returns a copy
    MATHDLL_API Vector2i operator-(void) const;  
    
    // Math Operators
    MATHDLL_API Vector2i operator+(const Vector2i& rhs) const;
    MATHDLL_API Vector2i operator-(const Vector2i& rhs) const;
    MATHDLL_API Vector2i operator*(const int rhs) const;
    MATHDLL_API Vector2i operator/(const int rhs) const;
    MATHDLL_API Vector2i & operator+=(const Vector2i& rhs);
    MATHDLL_API Vector2i & operator-=(const Vector2i& rhs);
    MATHDLL_API Vector2i & operator*=(const int rhs);
    MATHDLL_API Vector2i & operator/=(const int rhs);
  
    // Comparison operators
    MATHDLL_API bool operator==(const Vector2i& rhs) const;
    MATHDLL_API bool operator!=(const Vector2i& rhs) const;
         
    // Linear Algebra
    MATHDLL_API float    Length(void) const;
    MATHDLL_API int      LengthSq(void) const;
    MATHDLL_API void     Negate(void);
    MATHDLL_API Vector2  GetNormalized(void) const;
    MATHDLL_API int      Dot(const Vector2i& rhs) const;
    MATHDLL_API int      Cross(const Vector2i& rhs) const;

    MATHDLL_API void Zero(void);
    MATHDLL_API void Set(int xx=0, int yy=0);

    // Helpers
    MATHDLL_API void      Print(void) const;
    MATHDLL_API Vector2i  Min(const Vector2i& rhs);
    MATHDLL_API Vector2i  Max(const Vector2i& rhs);

    MATHDLL_API Vector2 to_f() const;

    MATHDLL_API int & operator[](int index);
    MATHDLL_API int operator[](int index) const;

    int x; 
    int y;
  };
}
