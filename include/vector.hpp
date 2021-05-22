#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

class Vec3 {
    public:
    double x, y, z;

    Vec3(double X =0, double Y = 0, double Z = 0): x(X), y(Y), z(Z){}

    static Vec3 approx(const Vec3& first, const Vec3& second) {
        double t = 3./ sqrt((second.x - first.x) * (second.x - first.x) +
                            (second.y - first.y) * (second.y - first.y) +
                            (second.z - first.z) * (second.z - first.z));
        Vec3 ans(
            first.x + (second.x - first.x)*t,
            first.y + (second.y - first.y)*t,
            first.z + (second.z - first.z)*t
        );
    }

    static double range(const Vec3& first, const Vec3& second){
        return sqrt((second.x - first.x) * (second.x - first.x) +
                    (second.y - first.y) * (second.y - first.y) +
                    (second.z - first.z) * (second.z - first.z));
    }
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
const double operator *(const Vec3& left, const Vec3& right) {
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
const Vec3 operator *(const Vec3& left, const double& c) {
    return Vec3(left.x * c, left.y * c, left.z * c);
}

// Деление на костанту
const Vec3 operator /(const Vec3& left, const double& c) {
    double f = 1./c;
    return Vec3(left.x * f, left.y * f, left.z * f);
}

std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    out << v.x << " " << v.y <<" "<< v.z << " ";
    return out;
}

#endif // VECTOR_HPP
