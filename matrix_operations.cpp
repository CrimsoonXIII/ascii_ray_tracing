#include "m_math/matrix_operations.h"

#include <cmath>
mat4 translate(vec3 v)
{
    return {{0,0,0,v.x},{0,0,0,v.y},{0,0,0,v.z},{0,0,0,0}};
}

mat4 translate(vec4 v)
{
    return {{0,0,0,v.x},{0,0,0,v.y},{0,0,0,v.z},{0,0,0,v.w}};
}

mat4 translate(float x, float y, float z)
{
    return {{0,0,0,x},{0,0,0,y},{0,0,0,z},{0,0,0,0}};
}

mat3 rotX(float rad)
{
    return {{1.0f, 0.0f, 1.0f },{0.0f ,cosf(rad),-sinf(rad)},{0.0f ,sinf(rad),cosf(rad)}};
}

mat3 rotY(float rad)
{
    return {{cosf(rad),0,sinf(rad)},{0,1,0},{-sinf(rad),0,cosf(rad)}};
}

mat3 rotZ(float rad)
{
    return {{cosf(rad),-sinf(rad),0},{sinf(rad),cosf(rad),0},{0,0,1}};
}

mat4 rotX(float rad, float a)
{
    return {{1,cosf(rad),-sinf(rad),0},{0,sinf(rad),cosf(rad),0},{0,0,1,0},{0,0,0,a}};
}

mat4 rotY(float rad, float a)
{
    return {{cosf(rad),0,sinf(rad),0},{0,1,0,0},{-sinf(rad),0,cosf(rad),0},{0,0,0,a}};
}

mat4 rotZ(float rad, float a)
{
    return {{cosf(rad),-sinf(rad),0,0},{sinf(rad),cosf(rad),0,0},{0,0,1,0},{0,0,0,a}};
}

mat4 rot(vec4 axis, float rad)
{
    float cosYZ;
    float angle1 = 0.0f;
    float cosXY;
    float angle2 = 0.0f;
    if(axis.z != 0 || axis.y != 0)
    {
        cosYZ = axis.y / sqrtf(axis.z * axis.z + axis.y * axis.y);
        angle1 = acosf(cosYZ);
        if(axis.z < 0)
            angle1 *= -1;
    }

    mat4 m1 = rotX(-angle1, 0.0f);
    axis = m1 * axis;
    if(axis.y!=0 || axis.x != 0)
    {
        cosXY = axis.x / sqrtf(axis.x * axis.x + axis.y * axis.y);
        angle2 = acos(cosXY);
        if(axis.y < 0)
            angle2 *= -1;
    }


    return rotX(angle1, 0.0f) * rotZ(angle2, 0.0f) * rotX(rad, 0.0f) * rotZ(-angle2, 0.0f) * m1;

}

mat3 rot(vec3 axis, float rad)
{
    float cosYZ;
    float angle1 = 0.0f;
    float cosXY;
    float angle2 = 0.0f;
    if(axis.z != 0 || axis.y != 0)
    {
        cosYZ = axis.y / sqrtf(axis.z * axis.z + axis.y * axis.y);
        angle1 = acosf(cosYZ);
        if(axis.z < 0)
            angle1 *= -1;
    }

    mat3 m1 = rotX(-angle1);
    axis = m1 * axis;
    if(axis.y!=0 || axis.x != 0)
    {
        cosXY = axis.x / sqrtf(axis.x * axis.x + axis.y * axis.y);
        angle2 = acos(cosXY);
        if(axis.y < 0)
            angle2 *= -1;
    }


    return rotX(angle1) * rotZ(angle2) * rotX(rad) * rotZ(-angle2) * m1;

}

mat4 rot(vec4 axis, vec4 anchor, float rad)
{
    float cosYZ;
    float angle1 = 0.0f;
    float cosXY;
    float angle2 = 0.0f;
    if(axis.z != 0 || axis.y != 0)
    {
        cosYZ = axis.y / sqrtf(axis.z * axis.z + axis.y * axis.y);
        angle1 = acosf(cosYZ);
        if(axis.z < 0)
            angle1 *= -1;
    }

    mat4 m1 = rotX(-angle1, 0.0f);
    axis = m1 * axis;
    if(axis.y!=0 || axis.x != 0)
    {
        cosXY = axis.x / sqrtf(axis.x * axis.x + axis.y * axis.y);
        angle2 = acos(cosXY);
        if(axis.y < 0)
            angle2 *= -1;
    }


    return translate(-axis) * rotX(angle1, 0.0f) * rotZ(angle2, 0.0f) * rotX(rad, 0.0f) * rotZ(-angle2, 0.0f) * m1* translate(axis);
}
