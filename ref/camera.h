#ifndef _CAMERA_H
#define _CAMERA_H

#include "vec3.h"
#include "ray.h"

class PinholeCamera
{
private:
    Vec3 cam_pos;  //カメラの位置座標
    Vec3 camera_f; //カメラの正面方向
    Vec3 camera_u; //上方向
    Vec3 camera_r; //横方向

public:
    PinholeCamera()
    {
        cam_pos = Vec3(0);
        camera_f = Vec3(1, 0, 0);

        camera_r = normalize(cross(camera_f, Vec3(0, 1, 0)));
        camera_u = normalize(cross(camera_r, camera_f));
    }

    PinholeCamera(const Vec3 &campos, const Vec3 &camdir)
    {
        cam_pos = campos;
        camera_f = camdir;

        //縦横を示す単位ベクトルの生成
        camera_r = normalize(cross(camera_f, Vec3(0, 1, 0)));
        camera_u = normalize(cross(camera_r, camera_f));
        std::cout << camera_r[0] << camera_r[1] << camera_r[2] << std::endl;
    }

    // uv [-1,1]の値をもらった時、対応する画素のレイを生成する
    Ray getCameraRay(float u, float v) const
    {
        u *= -1;
        v *= -1;
        Vec3 I_ij = cam_pos + u * camera_r + v * camera_u; //画素の位置
        Vec3 p = cam_pos + camera_f;                       //ピンホールの位置

        Ray cam_ray;
        cam_ray.origin = I_ij;
        cam_ray.direction = normalize(p - I_ij);

        return cam_ray;
    }
};
#endif