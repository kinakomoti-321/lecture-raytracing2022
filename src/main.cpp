#include <iostream>
#include <image.h>
#include "raytracing.h"
#include "camera.h"
#include "sphere.h"
#include "scene.h"
#include "material.h"

int main()
{

    Image img(512, 512);
    const unsigned int width = img.getWidth();
    const unsigned int height = img.getHeight();

    const Vec3 camPos(4, 1, 7);
    const Vec3 lookAt(0);

    PinholeCamera camera(camPos, normalize(lookAt - camPos));

    Scene scene;
    scene.addSphere(Sphere(Vec3(2, 0, -1), 1.0, Material::Diffuse, Vec3(0.2, 0.2, 0.8)));
    scene.addSphere(Sphere(Vec3(0, 0, 0), 1.0, Material::Diffuse, Vec3(0.8, 0.2, 0.2)));
    scene.addSphere(Sphere(Vec3(-2, 0, 1), 1.0, Material::Diffuse, Vec3(0.2, 0.8, 0.2)));

    scene.addSphere(Sphere(Vec3(-2, 3, 1), 1.0, Material::Mirror, Vec3(1)));
    scene.addSphere(Sphere(Vec3(3, 1, 2), 1.0, Material::Glass, Vec3(1)));
    scene.addSphere(Sphere(Vec3(0, -1001, 0), 1000, Material::Diffuse, Vec3(1)));

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            const float u = (2.0f * i - width) / height;
            const float v = (2.0f * j - height) / height;

            IntersectionInfo info;
            const Ray ray = camera.getCameraRay(u, v);
            img.setPixel(i, j, raytrace(scene, ray));
        }
    }

    img.writePPM("raytracing");

    return 0;
}