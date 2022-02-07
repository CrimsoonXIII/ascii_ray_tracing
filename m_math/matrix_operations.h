#pragma once
#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H
#include "m_math/vec3.h"
#include "m_math/vec4.h"
#include "m_math/mat3.h"
#include "m_math/mat4.h"

mat4 translate(vec3 v);
mat4 translate(vec4 v);
mat4 translate(float x, float y, float z);

mat3 rotX(float rad);
mat3 rotY(float rad);
mat3 rotZ(float rad);

mat4 rotX(float rad, float a);
mat4 rotY(float rad, float a);
mat4 rotZ(float rad, float a);

mat3 rot(vec3 axis, float rad);

mat4 rot(vec4 axis, float rad);

mat4 rot(vec3 axis, vec3 anchor, float rad);
mat4 rot(vec4 axis, vec4 anchor, float rad);

#endif // MATRIX_OPERATIONS_H
