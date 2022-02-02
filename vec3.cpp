#include <stdexcept>
#include "m_math/vec3.h"
#include <cmath>
vec3::vec3()
{

}
vec3::vec3(vec3 a, vec3 b)
{
   x = b.x - a.x;
   y = b.y - a.y;
   z = b.z - a.z;
}
vec3::vec3(float a)
{
    x = a;
    y = a;
    z = a;
}
vec3::vec3(float a, float b, float c)
{
    x = a;
    y = b;
    z = c;
}
vec3::vec3(float v[3])
{
    x = v[0];
    y = v[1];
    z = v[2];
}
float vec3::dot(vec3 v)
{
    return x * v.x + y * v.y + z * v.z;
}
vec3 vec3::cross(vec3 v)
{
    return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
}
float vec3::length()
{
    return std::sqrt(std::pow(x,2)+std::pow(y,2)+std::pow(z,2));
}
float& vec3::operator[](int a)
{
    if(a > 2 || a < 0)
        throw std::out_of_range("vec3::operator[]() out_of_range");
    return *(&x + a);
}
vec3 vec3::operator+(vec3 b)
{
    return {x + b.x, y + b.y, z + b.z};
}
vec3 vec3::operator-(vec3 b)
{
    return {x - b.x, y - b.y, z - b.z};
}
vec3 vec3::operator/(float a)
{
    return {x / a, y / a, z / a};
}
vec3 operator*(float a, vec3 v)
{
    return {v.x * a, v.y * a, v.z * a};
}
vec3 operator*(vec3 v, float a)
{
    return {v.x * a, v.y * a, v.z * a};
}
vec3 operator+(float a, vec3 v)
{
    return {v.x + a, v.y + a, v.z + a};
}
vec3 operator+(vec3 v, float a)
{
    return {v.x + a, v.y + a, v.z + a};
}
vec3 vec3::operator-()
{
    return {-x, -y, -z};
}
