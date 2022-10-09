#ifndef _SPHERE_H
#define _SPHERE_H

#include "intersectioninfo.h"
#include "vec3.h"
#include "ray.h"
#include "material.h"

class Sphere
{
private:
    Vec3 center;       //中心位置
    float radius;      //半径
    Material material; //材質を表すインデックス
    Vec3 color;        //球の色

public:
    Sphere(const Vec3 &center, const float radius, const Material material, const Vec3 color) : center(center), radius(radius), material(material), color(color){};

    //衝突判定
    // false : 衝突しなかった、true : 衝突する
    // ray 受け取ったレイ、これと衝突するか判定する

    bool intersect(const Ray &ray, IntersectionInfo &info) const
    {
        Vec3 oc = ray.origin - center;
        float b = dot(ray.direction, oc);
        float c = norm(oc) * norm(oc) - radius * radius;

        float D = b * b - c;

        //判定式 衝突しなかった場合
        if (D < 0)
        {
            return false;
        }

        //衝突する場合の処理
        float t1 = -b - std::sqrt(D);
        float t2 = -b + std::sqrt(D);

        float t = t1;
        // t1,t2は負ではない事、最小交差距離以上であること、最大交差距離以下であることが求められる
        if (t < ray.tmin || t > ray.tmax)
        {
            t = t2;
            if (t < ray.tmin || t > ray.tmax)
            {
                // t1,t2が制限に満たない場合、衝突しないものとする
                return false;
            }
        }

        info.t = t;
        info.position = ray.posT(t);
        info.normal = normalize(info.position - center);
        info.material = material;
        info.color = color;

        return true;
    }
};
#endif