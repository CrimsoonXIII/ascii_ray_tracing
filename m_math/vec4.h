#pragma once
#ifndef VEC4_H
#define VEC4_H

#include "m_math/vec3.h"

struct vec4
{
    float x;
    float y;
    float z;
    float w;
    vec4();
    vec4(vec4 a, vec4 b);
    vec4(float a);
    vec4(float a, float b, float c, float d);
    vec4(vec3 v, float a);
    vec4(vec3 v);
    vec4(float v[4]);
    float dot(vec4 b);
    float& operator[](int a);
    vec4 operator+(vec4 b);
    vec4 operator-(vec4 b);
    vec4 operator-();
    vec4 operator/(float a);
    friend vec4 operator*(float a, vec4 v);
    friend vec4 operator*(vec4 v, float a);
    friend vec4 operator+(float a, vec4 v);
    friend vec4 operator+(vec4 v, float a);
    operator vec3();
};
#endif // VEC4_H
