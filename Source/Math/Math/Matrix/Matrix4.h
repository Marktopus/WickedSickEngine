#pragma once

#include "Math/MathDLL.h"

namespace WickedSick
{
  struct Vector3;
  struct Vector4;

  struct Matrix4
  {
    union
    {
      struct  
      {
        float m00, m01, m02, m03,
              m10, m11, m12, m13,
              m20, m21, m22, m23,
              m30, m31, m32, m33;
      };
  
      float m[4][4];
      float v[16];
    };
  
    // Constructor
    MATHDLL_API Matrix4(void);
    MATHDLL_API Matrix4(const Matrix4& rhs);
    MATHDLL_API Matrix4(const float* a);
    MATHDLL_API Matrix4(float mm00, float mm01, float mm02, float mm03,
                        float mm10, float mm11, float mm12, float mm13,
                        float mm20, float mm21, float mm22, float mm23,
                        float mm30, float mm31, float mm32, float mm33);
  
    // Assignment operator, does not need to handle self-assignment
    MATHDLL_API Matrix4& operator=(const Matrix4& rhs);
  
    // Multiplying a Matrix4 with a Vector4 or a Point4
    MATHDLL_API Vector4 operator*(const Vector4& rhs) const;
  
    // Basic Matrix arithmetic operations
    MATHDLL_API Matrix4 operator+(const Matrix4& rhs) const;
    MATHDLL_API Matrix4 operator-(const Matrix4& rhs) const;
    MATHDLL_API Matrix4 operator*(const Matrix4& rhs) const;
    MATHDLL_API Matrix4& operator+=(const Matrix4& rhs);
    MATHDLL_API Matrix4& operator-=(const Matrix4& rhs);
    MATHDLL_API Matrix4& operator*=(const Matrix4& rhs);
    MATHDLL_API Matrix4 operator*(const float rhs) const;
    MATHDLL_API Matrix4 operator/(const float rhs) const;
    MATHDLL_API Matrix4& operator*=(const float rhs);
    MATHDLL_API Matrix4& operator/=(const float rhs);
  
    // Comparison operators
    MATHDLL_API bool operator==(const Matrix4& rhs) const;
    MATHDLL_API bool operator!=(const Matrix4& rhs) const;

    // Linear Algebra
    MATHDLL_API Matrix4 GetTranspose() const;
    MATHDLL_API void Transpose();
    MATHDLL_API void Inverse();

    // Settors
    MATHDLL_API Matrix4& Zero(void);
    MATHDLL_API Matrix4& Identity(void);
  
    MATHDLL_API Matrix4& Scale(const Vector3& scale);
    MATHDLL_API Matrix4 GetScaled(const Vector3& scale) const;

    MATHDLL_API Matrix4& RotateX(float x);
    MATHDLL_API Matrix4& RotateY(float y);
    MATHDLL_API Matrix4& RotateZ(float z);
    MATHDLL_API Matrix4 GetRotatedX(float x) const;
    MATHDLL_API Matrix4 GetRotatedY(float y) const;
    MATHDLL_API Matrix4 GetRotatedZ(float z) const;

    MATHDLL_API Matrix4& RotateXYZ(const Vector3& rot);
    MATHDLL_API Matrix4 GetRotatedXYZ(const Vector3& rot) const;

    MATHDLL_API Matrix4& Translate(const Vector3& dist);
    MATHDLL_API Matrix4 GetTranslated(const Vector3& dist) const;

    // Other
    MATHDLL_API void Print(void) const;


    //graphics
    MATHDLL_API Matrix4& DoPerspective(float fovW, float znear, float zfar, float aspectRatio);
    MATHDLL_API Matrix4& DoOrthographic(int width, int height, float znear, float zfar);
  };
}

