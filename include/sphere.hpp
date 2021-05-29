#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>
#include <limits>
#include <tuple>

#include "solid.hpp"
#include "vector.hpp"

double DELTA = 0.1;

class Sphere : Solid {
    public:
    Vec3 center;
    double radius;

    Sphere(const Vec3 &c = Vec3(), const double &r = 0.) : center(c), radius(r) {}

    Vec3 reflection(const Vec3& src, const Vec3& dst, const Vec3& collision) {
        Vec3 V = dst - src;
        Vec3 N = collision - center;
        Vec3 R = -2 * (V* N) ^ N + V;
        return R;
    }

    virtual std::tuple<bool, Vec3> collision(const Vec3& first, const Vec3& second) const {
        // сократить расстояние вектора до приемлемых значений (не надо)

        double a = (second.x - first.x) * (second.x - first.x) +
                   (second.y - first.y) * (second.y - first.y) +
                   (second.z - first.z) * (second.z - first.z);
        double b = -2*((first.x - center.x) * (second.x - first.x) +
                       (first.y - center.y) * (second.y - first.y) +
                       (first.z - center.z) * (second.z - first.z));
        double c = (first.x - center.x) * (first.x - center.x) +
                   (first.y - center.y) * (first.y - center.y) +
                   (first.z - center.z) * (first.z - center.z) -
                   radius * radius;

        double D = b*b - 4*a*c;

        double t = (-b + std::sqrt(D))/(2*a);
        if (D >= 0){
            Vec3 collision(
                first.x + (second.x - first.x)*t,
                first.y + (second.y - first.y)*t,
                first.z + (second.z - first.z)*t
            );

            // collision = collision + (collision - center) * DELTA / Vec3::range(collision, center);
            return std::tuple<double, Vec3>(std::move(true), std::move(collision));
        }
        else{
            return std::tuple<double, Vec3>(std::move(false),std::move( Vec3()));
        }
    }
};

class LightSphere : public Sphere{
    public:
    LightSphere(const Vec3 &c, const double &r) : Sphere(c, r){
    }
};

#endif // SPHERE_HPP
