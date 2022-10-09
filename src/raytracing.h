#ifndef _RAYTRACING_H
#define _RAYTRACING_H

#include "vec3.h"
#include "scene.h"
#include "ray.h"
#include "intersectioninfo.h"
#include "material.h"
#include <cmath>

// SceneとRayを受け取ったら色を返す関数
inline Vec3 raytrace(const Scene &scene, const Ray &ray)
{
    IntersectionInfo info;
    Vec3 wi = normalize(Vec3(1, 1, 1));
    if (scene.intersect(ray, info))
    {
        //球に衝突した時の処理
        return std::max(dot(info.normal, wi), 0.0f) * info.color;
    }
    else
    {
        //球に衝突しなかった時の処理
        return Vec3(0);
    }
}

#endif