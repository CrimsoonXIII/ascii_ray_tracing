#pragma once
#ifndef VEC3_H
#define VEC3_H

struct vec3
{
    float x, y, z;
    vec3();
    vec3(vec3 a, vec3 b);
    vec3(float a);
    vec3(float a, float b, float c);
    vec3(float v[3]);
    float dot(vec3 b);
    vec3 cross(vec3 b);
    float length();
    float& operator[](int a);
    vec3 operator+(vec3 b);
    vec3 operator-(vec3 b);
    vec3 operator/(float b);
    friend vec3 operator*(float a, vec3 v);
    friend vec3 operator*(vec3 v, float a);
    friend vec3 operator+(float a, vec3 v);
    friend vec3 operator+(vec3 v, float a);
    vec3 operator-();
};
#endif // VEC3_H
