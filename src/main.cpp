#include <iostream>
#include <image.h>

int main()
{
    Image img(512, 512);
    const unsigned int width = img.getWidth();
    const unsigned int height = img.getHeight();

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            Vec3 RGB(static_cast<float>(i) / width, static_cast<float>(j) / height, 1.0f);
            img.setPixel(i, j, RGB);
        }
    }

    img.writePPM("test");

    return 0;
}