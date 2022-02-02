#include <stdexcept>
#include "m_math/vec4.h"

vec4::vec4()
{

}

vec4::vec4(vec4 a, vec4 b)
{
    x = b.x - a.x;
    y = b.y - a.y;
    z = b.z - a.z;
    w = b.w - a.w;
}

vec4::vec4(float a)
{
    x = a;
    y = a;
    z = a;
    w = a;
}
vec4::vec4(float a, float b, float c, float d)
{
    x = a;
    y = b;
    z = c;
    w = d;
}
vec4::vec4(vec3 v, float a)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = a;
}

vec4::vec4(vec3 v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = 0.0f;
}

vec4::vec4(float v[4])
{
    x = v[0];
    y = v[1];
    z = v[2];
    w = v[3];
}
float vec4::dot(vec4 b)
{
    return x * b.x + y * b.y + z * b.z + w * b.w;
}
float& vec4::operator[](int a)
{
    if(a > 3 || a < 0)
        throw std::out_of_range("vec4::operator[]() out_of_range");
    return *(&x + a);
}
vec4 vec4::operator+(vec4 b)
{
    return {x + b.x, y + b.y, z + b.z, w + b.w};
}
vec4 vec4::operator-(vec4 b)
{
    return {x - b.x, y - b.y, z - b.z, w - b.w};
}
vec4 vec4::operator/(float a)
{
    return {x / a, y / a, z / a, w / a};
}
vec4 vec4::operator-()
{
    return {-x, -y, -z, -w};
}
vec4 operator*(float a, vec4 v)
{
    return {v.x * a, v.y * a, v.z * a, v.w * a};
}
vec4 operator*(vec4 v, float a)
{
    return {v.x * a, v.y * a, v.z * a, v.w * a};
}
vec4 operator+(float a, vec4 v)
{
    return {v.x + a, v.y + a, v.z + a, v.w + a};
}
vec4 operator+(vec4 v, float a)
{
    return {v.x + a, v.y + a, v.z + a, v.w + a};
}
vec4::operator vec3()
{
    return {x,y,z};
}
