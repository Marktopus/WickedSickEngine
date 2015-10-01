#pragma once

#include "MathDLL.h"

namespace WickedSick
{
  struct Vector3;

  struct Matrix3
  {
    union
    {
      struct  
      {
        float m00, m01, m02,
              m10, m11, m12,
              m20, m21, m22;
      };
  
      float m[3][3];
      float v[9];
    };
  
    // Constructors
    MATHDLL_API Matrix3(void);
    MATHDLL_API Matrix3(const Matrix3& rhs);
    MATHDLL_API Matrix3(float mm00, float mm01, float mm02,
                        float mm10, float mm11, float mm12,
                        float mm20, float mm21, float mm22);
  
    // Assignment operator, does not need to handle self-assignment
    MATHDLL_API Matrix3& operator=(const Matrix3& rhs);
  
    // Multiplying a Matrix3 with a Vector3 or a Point3
    MATHDLL_API Vector3 operator*(const Vector3& rhs) const;
  
    // Basic Matrix arithmetic operations
    MATHDLL_API Matrix3 operator+(const Matrix3& rhs) const;
    MATHDLL_API Matrix3 operator-(const Matrix3& rhs) const;
    MATHDLL_API Matrix3 operator*(const Matrix3& rhs) const;
    MATHDLL_API Matrix3& operator+=(const Matrix3& rhs);
    MATHDLL_API Matrix3& operator-=(const Matrix3& rhs);
    MATHDLL_API Matrix3& operator*=(const Matrix3& rhs);
    MATHDLL_API Matrix3 operator*(const float rhs) const;
    MATHDLL_API Matrix3 operator/(const float rhs) const;
    MATHDLL_API Matrix3& operator*=(const float rhs);
    MATHDLL_API Matrix3& operator/=(const float rhs);
  
    // Comparison operators 
    MATHDLL_API bool operator==(const Matrix3& rhs) const;
    MATHDLL_API bool operator!=(const Matrix3& rhs) const;

    // Linear Algebra
    MATHDLL_API void Transpose();
    MATHDLL_API void Inverse();

    //rotation
    MATHDLL_API void MakeRotateX(float x);
    MATHDLL_API void MakeRotateY(float y);
    MATHDLL_API void MakeRotateZ(float z);

    // Settors
    MATHDLL_API void Zero(void);
    MATHDLL_API void Identity(void);
  
    // Other
    MATHDLL_API void Print(void) const;
  };
}

