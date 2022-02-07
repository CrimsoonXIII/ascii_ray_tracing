#pragma once
#ifndef MAT4_H
#define MAT4_H

#include "m_math/vec4.h"
#include "m_math/mat3.h"
struct mat4 // 4x4 matrix
{
    vec4 v0;
    vec4 v1;
    vec4 v2;
    vec4 v3;
    mat4();
    mat4(float a);
    mat4(vec4 a, vec4 b, vec4 c, vec4 d);
    mat4(mat3 m, float a);
    vec4& operator[](int a);
    vec4 operator*(vec4 b);
    mat4 operator*(mat4 b);
};

#endif // MAT4_H
