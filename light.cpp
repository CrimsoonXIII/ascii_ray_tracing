#include "light.h"

point_light::point_light(float i, float x, float y, float z)
{
    intensity = i;
    pos = {x,y,z};
}
point_light::point_light(float i, vec3 p)
{
    intensity = i;
    pos = p;
}
