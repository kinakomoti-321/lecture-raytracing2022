#include <iostream>
#include <image.h>
#include "camera.h"
#include "sphere.h"

int main()
{
    Image img(512, 512);
    const unsigned int width = img.getWidth();
    const unsigned int height = img.getHeight();

    PinholeCamera camera(Vec3(0, 0, 3), Vec3(0, 0, -1));

    Sphere sphere(Vec3(0), 1.0, 1, Vec3(1, 1, 1));

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            const float u = (2.0f * i - width) / height;
            const float v = (2.0f * j - height) / height;

            IntersectionInfo info;
            const Ray ray = camera.getCameraRay(u, v);

            if (sphere.intersect(ray, info))
            {
                img.setPixel(i, j, 0.5f * (info.normal + Vec3(1)));
            }
            else
            {
                img.setPixel(i, j, Vec3(0));
            }
        }
    }

    img.writePPM("test");

    return 0;
}