#ifndef LIGHT_H
#define LIGHT_H
#include "m_math.h"

struct point_light
{
    public:
        float intensity = 0.0f;
        vec3 pos = {0.0f, 0.0f, 0.0f};
        point_light(float i, float x, float y, float z);
        point_light(float i, vec3 pos);

};

#endif // LIGHT_H
