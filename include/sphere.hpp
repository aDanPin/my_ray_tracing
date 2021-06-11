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
        Vec3 ri = approx(dst - src, 1);
        Vec3 n  = approx(collision - center, 1);

        Vec3 a = ri -  n * 2 * (n * ri);

        return a;
    }

    virtual std::tuple<bool, Vec3> collision(const Vec3& src, const Vec3& dir) const {
        bool collision_was = false;
        Vec3 collision = Vec3();

        Vec3 S = src - center;
        Vec3 d = dir - src;

        double a = (dir.x - src.x) * (dir.x - src.x) +
                   (dir.y - src.y) * (dir.y - src.y) +
                   (dir.z - src.z) * (dir.z - src.z);
        double b = 2*((src.x - center.x) * (dir.x - src.x) +
                       (src.y - center.y) * (dir.y - src.y) +
                       (src.z - center.z) * (dir.z - src.z));
        double c = (src.x - center.x) * (src.x - center.x) +
                   (src.y - center.y) * (src.y - center.y) +
                   (src.z - center.z) * (src.z - center.z) -
                   radius * radius;

        double D = b*b - 4*a*c;

        if (D >= 0) {
            double t1 = (-b - std::sqrt(D)) / (2*a);

            if (t1 > 0) {
                collision_was = true;
                collision = src + d * t1;

                return std::make_tuple<bool, Vec3>(std::move(collision_was), std::move(collision));
            }

            double t2 = (-b + std::sqrt(D)) / (2*a);
            if (t2 > 0) {
                collision_was = true;
                collision = src + d * t2;

                return std::make_tuple<bool, Vec3>(std::move(collision_was), std::move(collision));
            }
        } else {
            return std::make_tuple<bool, Vec3>(std::move(collision_was), std::move(collision));
        }
    }

};

class LightSphere : public Sphere{
    public:
    LightSphere(const Vec3 &c, const double &r) : Sphere(c, r){
    }
};

#endif // SPHERE_HPP
