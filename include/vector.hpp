#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

class Vec3 {
    public:
    float x, y, z;

    Vec3(float X =0, float Y = 0, float Z = 0): x(X), y(Y), z(Z){}
};

    Vec3& operator+=( Vec3& left, const Vec3& right) {
        left.x += right.x;
        left.y += right.y;
        left.z += right.z;
        return left;
    }

    Vec3& operator-=( Vec3& left, const Vec3& right) {
        left.x -= right.x;
        left.y -= right.y;
        left.z -= right.z;
        return left;
    }

    const Vec3 operator+(const Vec3& left) {
        return Vec3(left);
    }

    const Vec3 operator-(const Vec3& left) {
        return  Vec3(-left.x, -left.y, -left.z);
    }

    const Vec3 operator+(const Vec3& left, const Vec3& right) {
        return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
    }

    const Vec3 operator-(const Vec3& left, const Vec3& right) {
        return Vec3(left.x - right.x, left.y - right.y, left.z - right.z);
    }

    // Скалярное произведение
    const float operator *(const Vec3& left, const Vec3& right) {
        return left.x * right.x + left.y * right.y + left.z + right.z;
    }

    // Векторное произведение
    const Vec3 operator ^(const Vec3& left, const Vec3& right) {
        return Vec3(left.y * right.z - left.z * right.y,
                    left.z * right.x - left.x * right.z,
                    left.x * right.y - left.y * right.x);
    }

    // Произведение на костанту
    const Vec3 operator *(const Vec3& left) {
        return Vec3(left);
    }

    // Произведение на костанту
    const Vec3 operator *(const Vec3& left, const float& c) {
        return Vec3(left.x * c, left.y * c, left.z * c);
    }

    // Деление на костанту
    const Vec3 operator /(const Vec3& left, const float& c) {
        float f = 1./c;
        return Vec3(left.x * f, left.y * f, left.z * f);
    }


#endif // VECTOR_HPP
