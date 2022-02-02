#include <stdexcept>
#include "m_math/mat4.h"

mat4::mat4():v0(), v1(), v2(), v3()
{

}
mat4::mat4(float a):v0(a, 0.0f, 0.0f, 0.0f), v1(0.0f, a, 0.0f, 0.0f), v2(0.0f, 0.0f, a, 0.0f), v3(0.0f, 0.0f, 0.0f, a)
{

}
mat4::mat4(vec4 a, vec4 b, vec4 c, vec4 d)
{
    v0 = a;
    v1 = b;
    v2 = c;
    v3 = d;
}
mat4::mat4(mat3 m, float a):v0(m.v0, 0.0f), v1(m.v1, 0.0f), v2(m.v2, 0.0f), v3(0.0f, 0.0f, 0.0f, a)
{

}
vec4& mat4::operator[](int a)
{
    if(a > 3 || a < 0)
        throw std::out_of_range("mat4::operator[]() out_of_range");
    vec4 & v = *(&v0 + a);
    return v;
}
vec4 mat4::operator*(vec4 b)
{
    return {b.dot(v0), b.dot(v1), b.dot(v2), b.dot(v3)};
}
mat4 mat4::operator*(mat4 b)
{
    mat4 c;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            c[i][j] = (*this)[i].dot({b[0][j], b[1][j], b[2][j], b[3][j]});
        }
    return c;
}
