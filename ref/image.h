#ifndef _IMAGE_H
#define _IMAGE_H

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include "./vec3.h"

class Image
{
private:
    unsigned int width;
    unsigned int height;
    float *pixel;

public:
    Image()
    {
        width = 1;
        height = 1;
        pixel = new float[width * height * 3];
    }

    Image(unsigned int width, unsigned int height) : width(width), height(height)
    {
        pixel = new float[width * height * 3];
    }

    ~Image()
    {
        delete[] pixel;
    }

    unsigned int getWidth() const { return width; };
    unsigned int getHeight() const { return height; };

    void setPixel(unsigned int i, unsigned int j, const Vec3 &RGB)
    {
        unsigned int index = (i + j * width) * 3;
        pixel[index] = RGB[0];
        pixel[index + 1] = RGB[1];
        pixel[index + 2] = RGB[2];
    }

    void writePPM(const std::string &filename) const
    {
        std::ofstream file(filename + ".ppm");
        file << "P3" << std::endl;
        file << width << " " << height << std::endl;
        file << "255" << std::endl;

        for (int j = 0; j < width; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                unsigned int index = (i + j * width) * 3;
                Vec3 RGB(pixel[index], pixel[index + 1], pixel[index + 2]);
                Vec3 G_RGB = gammaConver(RGB);
                const unsigned int R = static_cast<unsigned int>(255 * G_RGB[0]);
                const unsigned int G = static_cast<unsigned int>(255 * G_RGB[1]);
                const unsigned int B = static_cast<unsigned int>(255 * G_RGB[2]);

                file << R << " " << G << " " << B << std::endl;
            }
        }

        file.close();
    }

    Vec3 gammaConver(const Vec3 &RGB) const
    {
        Vec3 G_RGB;
        G_RGB[0] = std::pow(RGB[0], 1.0f / 2.2f);
        G_RGB[1] = std::pow(RGB[1], 1.0f / 2.2f);
        G_RGB[2] = std::pow(RGB[2], 1.0f / 2.2f);

        return G_RGB;
    }
};

#endif