#ifndef _INFO_H
#define _INFO_H

#include "vec3.h"

struct IntersectionInfo
{
    float t;       //交差位置までの距離
    Vec3 position; //交差位置
    Vec3 normal;   //法線
};

#endif