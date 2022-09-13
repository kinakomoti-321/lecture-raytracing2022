#ifndef _VEC3_H
#define _VEC3_H

#include <cmath>

class Vec3
{
public:
    float v[3];

    Vec3()
    {
        v[0] = 0;
        v[1] = 0;
        v[2] = 0;
    }

    Vec3(float t)
    {
        v[0] = t;
        v[1] = t;
        v[2] = t;
    }

    Vec3(float a, float b, float c)
    {
        v[0] = a;
        v[1] = b;
        v[2] = c;
    }

    float operator[](unsigned int i) const { return v[i]; };
    float &operator[](unsigned int i) { return v[i]; };

    Vec3 operator-() const
    {
        return Vec3(-v[0], -v[1], -v[2]);
    }

    Vec3 &operator+=(const Vec3 &vec)
    {
        v[0] += vec[0];
        v[1] += vec[1];
        v[2] += vec[2];
    }

    Vec3 &operator-=(const Vec3 &vec)
    {
        v[0] -= vec[0];
        v[1] -= vec[1];
        v[2] -= vec[2];
    }

    Vec3 &operator*=(const Vec3 &vec)
    {
        v[0] *= vec[0];
        v[1] *= vec[1];
        v[2] *= vec[2];
    }

    Vec3 &operator/=(const Vec3 &vec)
    {
        v[0] /= vec[0];
        v[1] /= vec[1];
        v[2] /= vec[2];
    }
};

float norm(const Vec3 &v)
{
    return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
{
    Vec3 result;
    for (int i = 0; i < 3; i++)
    {
        result[i] = v1[i] + v2[i];
    }

    return result;
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
{
    Vec3 result;
    for (int i = 0; i < 3; i++)
    {
        result[i] = v1[i] + v2[i];
    }

    return result;
}

inline Vec3 operator*(const float &f, const Vec3 &v)
{
    Vec3 result;
    for (int i = 0; i < 3; i++)
    {
        result[i] = v[i] * f;
    }
    return result;
}

inline Vec3 operator*(const Vec3 &v, const float &f)
{
    Vec3 result;
    for (int i = 0; i < 3; i++)
    {
        result[i] = v[i] * f;
    }
    return result;
}

inline Vec3 operator/(const Vec3 &v, const float &f)
{
    Vec3 result;
    for (int i = 0; i < 3; i++)
    {
        result[i] = v[i] / f;
    }
    return result;
}

//アダマール積
inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
{
    Vec3 result;
    for (int i = 0; i < 3; i++)
    {
        result[i] = v1[i] * v2[i];
    }
    return result;
}

//内積
inline float dot(const Vec3 &v1, const Vec3 &v2)
{
    float sum = 0;
    for (int i = 0; i < 3; i++)
    {
        sum += v1[i] * v2[i];
    }

    return sum;
}

//外積
inline Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
    Vec3 ret;
    ret[0] = v1[1] * v2[2] - v1[2] * v2[1];
    ret[1] = v1[2] * v2[0] - v1[0] * v2[2];
    ret[2] = v1[0] * v2[1] - v1[1] * v2[0];

    return ret;
}

//正規化　与えられたベクトルを単位ベクトル（大きさ１)にする
inline Vec3 normalize(const Vec3 &v)
{
    return v / norm(v);
}
#endif