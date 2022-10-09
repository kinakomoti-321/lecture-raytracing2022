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

    PinholeCamera camera(Vec3(0, 0, 5), Vec3(0, 0, -1));

    Scene scene;
    scene.addSphere(Sphere(Vec3(1, 0, 1), 1.0, Material::Diffuse, Vec3(1)));
    scene.addSphere(Sphere(Vec3(0, 0, 0), 1.0, Material::Diffuse, Vec3(1)));
    scene.addSphere(Sphere(Vec3(1, 0, -1), 1.0, Material::Diffuse, Vec3(1)));

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