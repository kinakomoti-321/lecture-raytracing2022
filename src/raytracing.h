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
    Vec3 wi = normalize(Vec3(1, 2, 1));
    Vec3 emviroment(0.1);
    Vec3 lightcolor(1);
    Vec3 color = Vec3(1);
    unsigned int MAX_DEPTH = 10;
    Ray next_ray = ray;
    for (int i = 0; i < MAX_DEPTH; i++)
    {
        IntersectionInfo info;
        if (scene.intersect(next_ray, info))
        {
            //物体に当たった場合
            if (info.material == Material::Diffuse)
            {
                // Diffuseの場合
                Ray shadow_ray;
                shadow_ray.origin = info.position;
                shadow_ray.direction = wi;

                IntersectionInfo shadow_info;
                if (scene.intersect(shadow_ray, shadow_info))
                {
                    color = emviroment;
                    break;
                }
                else
                {
                    color = std::max(dot(wi, info.normal), 0.0f) * lightcolor * info.color + emviroment;
                    break;
                }
            }
            else if (info.material == Material::Mirror)
            {
                // Mirrorの場合
                //次に進むレイを計算する
                next_ray.origin = info.position;
                next_ray.direction = reflect(-next_ray.direction, info.normal);
            }
            else if (info.material == Material::Glass)
            {
                next_ray.origin = info.position;

                float ior1, ior2;
                Vec3 normal;
                if (dot(-next_ray.direction, info.normal) < 0)
                {
                    //内側→外側
                    ior1 = 1.5;
                    ior2 = 1.0;
                    normal = -info.normal;
                }
                else
                {
                    //外側→内側
                    ior1 = 1.0;
                    ior2 = 1.5;
                    normal = info.normal;
                }

                Vec3 t;
                if (refract(-next_ray.direction, normal, ior1, ior2, t))
                {
                    //屈折する場合
                    next_ray.direction = t;
                }
                else
                {
                    //全反射する場合
                    next_ray.direction = reflect(-next_ray.direction, normal);
                }
            }
        }
        else
        {
            //物体に当たらなかった場合
            color = Vec3(0);
            break;
        }
    }

    return color;
}

#endif