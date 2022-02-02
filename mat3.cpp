#include <stdexcept>
#include "m_math/mat3.h"

mat3::mat3():v0(), v1(), v2()
{

}
mat3::mat3(float a):v0(a, 0.0f, 0.0f), v1(0.0f, a, 0.0f), v2(0.0f, 0.0f, a)
{

}
mat3::mat3(vec3 a, vec3 b, vec3 c)
{
    v0 = a;
    v1 = b;
    v2 = c;
}
vec3& mat3::operator[](int a)
{
    if(a > 2 || a < 0)
        throw std::out_of_range("mat3::operator[]() out_of_range");
    vec3 & v = *(&v0 + a);
    return v;
}
vec3 mat3::operator*(vec3 b)
{
    return {b.dot(v0), b.dot(v1), b.dot(v2)};
}
mat3 mat3::operator*(mat3 b)
{
    mat3 c;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            c[i][j] = (*this)[i].dot({b[0][j], b[1][j], b[2][j]});
        }
    return c;
}

