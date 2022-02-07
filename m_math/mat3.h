#pragma once
#ifndef MAT3_H
#define MAT3_H
#include "m_math/vec3.h"

struct mat3 // 3x3 matrix
{
    vec3 v0;
    vec3 v1;
    vec3 v2;
    mat3();
    mat3(float a);
    mat3(vec3 a, vec3 b, vec3 c);
    vec3& operator[](int a);
    vec3 operator*(vec3 b);
    mat3 operator*(mat3 b);
};

#endif // MAT3_H
