#ifndef _RAY_H
#define _RAY_H
#include "./vec3.h"

struct Ray
{
    Vec3 origin;
    Vec3 direction;
    float tmin = 1e-3f;
    float tmax = 1e5f;

    Ray() {}
    Ray(const Vec3 &origin, const Vec3 &direction) : origin(origin), direction(direction){};

    Vec3 posT(float t)
    {
        return origin + t * direction;
    }
};
#endif