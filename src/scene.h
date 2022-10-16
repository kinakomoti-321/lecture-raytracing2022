#ifndef _SCENE_H
#define _SCENE_H

#include "sphere.h"
#include "intersectioninfo.h"
#include "ray.h"

#include <vector>

class Scene
{
private:
    // Sphere Classの配列
    std::vector<Sphere> sphere;

public:
    Scene() {}
    ~Scene() {}

    //球体の追加
    void addSphere(const Sphere &in_sphere)
    {
        sphere.push_back(in_sphere);
    }

    //複数の球体に対する衝突判定
    bool intersect(const Ray &ray, IntersectionInfo &info) const
    {
        bool is_intersected = false;
        info.t = ray.tmax;

        for (int i = 0; i < sphere.size(); i++)
        {
            IntersectionInfo s_info;
            if (sphere[i].intersect(ray, s_info))
            {
                if (info.t > s_info.t)
                {
                    info = s_info;
                    is_intersected = true;
                }
            }
        }

        return is_intersected;
    }
};
#endif
